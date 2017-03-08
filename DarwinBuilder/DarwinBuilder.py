#!/usr/bin/env python3.6

from DarwinBuilder import *

# Give the user our version.
Utils.Log('Info', "This is DarwinBuilder v0.1-unstable.")

# Get versions of macOS. Use the second latest version, as the latest doesn't
# always have projects that we need (like Libc, CF, mDNSresponder, etc...)
macOSVersions = GetVersions.GetMacOSVersions()
macOSVersion = macOSVersions[1]

Utils.Log('Info', ("Using macOS release "
                   + Utils.InlineInfo(macOSVersion['full']) + "."))

DLSoftware.GetSources(macOSVersion)

SDKs.PrepareSDKs(macOSVersion['raw-id'])

BuildSoftware.BuildSources(macOSVersion['raw-id'])

Utils.Log('Success', ("Finished, your ISO is: darwin-"
                      + DLSoftware.BuildID + ".iso"))
