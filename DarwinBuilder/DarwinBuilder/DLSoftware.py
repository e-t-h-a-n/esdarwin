#!/usr/bin/env python3.6

import urllib.request, urllib.error, urllib.parse, socket, os, os.path, sys
import plistlib

from . import Utils

BuildID = ''

def GetSources(macOSVersion):
    RawMacOSVersion = macOSVersion['raw-id']
    FullMacOSVersion = macOSVersion['full']

    ParsePlist(RawMacOSVersion, FullMacOSVersion)
    DLTarballs(RawMacOSVersion)
    ExtractAll(RawMacOSVersion)
    PatchFiles(RawMacOSVersion)

# You may want to use code folding to hide this :O
def DLOrUseLocalCopy(URL, file, desc, quiet=False):
    # Try to download the file at URL and save it to file, else read from file
    # if file exists.

    # Our own DarwinBuilder folder
    file = '.db/' + file

    if (not (URL.startswith('https://') or URL.startswith('file://') or URL.startswith('http://localhost/'))) and (not quiet):
        # Uh oh, not using HTTPS!
        Utils.Log('Warning', "Not using HTTPS, this is insecure.")

    try:
        # Log to the user :)
        if not quiet:
            Utils.Log('Info', ("Trying to get " + desc
                               + " (at: " + Utils.InlineInfo(URL) + ")"))

        # Open the URL and decode it from a sequence of bytes into a UTF-8
        # string.
        response = urllib.request.urlopen(URL)
        output   = response.read().decode(encoding='utf-8')

        # Make the directory for the file, open the file, and write the
        # contents of the URL to it.
        os.makedirs(os.path.split(file)[0], exist_ok=True)
        FileDesc = open(file, 'wt')
        FileDesc.write(output)
        FileDesc.close()

        if not quiet:
            Utils.Log('Success', "Got " + desc + " over internet connection.")

    except (urllib.error.URLError, socket.gaierror) as e:
        # Argh, urllib.request.urlooen() failed :(

        CacheExists = os.path.exists(file)
        CacheUsable = not Utils.args['no_caches']

        if CacheExists and CacheUsable:
            # If we can continue, mark this as a warning.
            status = 'Warning'
        else:
            # If we can't continue mark this as an error.
            status = 'Error'

        if not quiet:
            # Log to the user, only print as an error if we can't continue.
            Utils.Log(status, ("Could not get " + desc + " at: "
                               + Utils.InlineInfo(URL)))
            Utils.Log('Indent', "Please check your internet connection.")
            Utils.Log('Indent', ("urllib.request.urlopen() returned: "
                                 + e.reason.strerror) + ".")

        if CacheExists and CacheUsable:
            # Read the cached version, if present and the user allows doing
            # so.
            FileDesc = open(file)
            output   = FileDesc.read()
            FileDesc.close()
        if not quiet:
            if CacheExists and CacheUsable:
                Utils.Log('Success', ("Got " + desc
                                      + " from locally cached copy."))
            elif CacheExists and not CacheUsable:
                # Print an error, as the user won't let us use a cached copy.
                Utils.Log('Indent', "Not using cache, '-C' given.")
            elif CacheUsable and not CacheExists:
                # Cached version wasn't found so give an error.
                Utils.Log('Indent', ("Cached version of " + desc
                                     + " not found."))
            elif (not CacheExists) and (not CacheUsable):
                # The cache couldn't be found and the user gave -C, so give an
                # error.
                Utils.Log('Indent', ("Cached version of " + desc
                                     + " not found " + "and -C option given."))

        if status == 'Error':
            # If the cache couldn't be used, for whatever reason, exit.
            sys.exit(1)

    return output

def ParsePlist(RawMacOSVersion, FullMacOSVersion):
    # Get the DarwinBuilder configuration Plist.
    ConfigPlist = DLOrUseLocalCopy(Utils.PlistSite(RawMacOSVersion),
                             ('darwinbuilder-files/releases/macOS '
                              + FullMacOSVersion + '/' + RawMacOSVersion
                              + '.tobuild.plist'),
                             ("DarwinBuilder macOS " + FullMacOSVersion
                              + " configuration plist"))\
                             .encode(encoding='utf-8')

    ConfigPlist = plistlib.loads(ConfigPlist)

    # Get Apple's macOS version Plist.
    macOSPlist = DLOrUseLocalCopy(('https://opensource.apple.com/plist/'
                                   + RawMacOSVersion + '.plist'),
                                  ('AppleOpenSource/plist/'
                                   + RawMacOSVersion + '.plist'),
                                  ("Apple's " + FullMacOSVersion
                                   + " macOS version plist"))\
                                  .encode(encoding='utf-8')

    macOSPlist = plistlib.loads(macOSPlist)

    # Set the Build Identifier.
    global BuildID
    BuildID = macOSPlist['build']

def DLTarballs(RawMacOSVersion):
    pass

def ExtractAll(RawMacOSVersion):
    pass

def PatchFiles(RawMacOSVersion):
    pass
