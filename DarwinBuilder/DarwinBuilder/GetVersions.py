#!/usr/bin/env python3.6

import html.parser, re, distutils.version

from . import Utils, DLSoftware

class AppleOpenSourceReleasesParser(html.parser.HTMLParser):
    def __init__(self):
        # On creation of the class, create an array for the resulting
        # versions, and a temporary variable used to store the version's
        # identifier as the site is being parsed.
        self.Versions = []
        self.__ver = ''

        # Initialise the base class.
        html.parser.HTMLParser.__init__(self)

    def handle_starttag(self, tag, attrs):
        # When we get to the start of a tag:

        for attr in list(sum(attrs, ())):
            # Iterate throught attrs. list(sum(blah, ())) flattens a list of
            # tuples to a single list. Empty the temporary variable, then
            # check to see if the attribute matches the regular expression,
            # and if so, store the match in the temporary variable created
            # earlier.

            self.__ver = ''
            match = re.search(r"^/release/(?P<macos_ver>(((mac-)?os-x)|macos)"
                              + "-\d+).html$", attr.strip())
            if match:
                self.__ver = match.group('macos_ver')

    def handle_data(self, data):
        # When we get to the contents of a tag (i.e. 'data' in
        # <tag>data</tag>.):

        # Check to see if the data is an OS X version (by regualar
        # expression), and if we've found a raw version identifier. If so,
        # add a dictionary to our "Versions" list.

        match = re.search(r"(?P<full_ver>10\.[\.\d]+)", data.strip())
        if match and self.__ver != '':
            self.Versions.append({'full': match.group('full_ver'),
                                 'raw-id': self.__ver})
    def feed(self, data):
        # Augment the existing feed() method by sorting the Versions list
        # by the value of each dictionary's 'full' key when done.

        html.parser.HTMLParser.feed(self, data)
        self.Versions = sorted(self.Versions, key=lambda k:
                               distutils.version.StrictVersion(k['full']),
                               reverse=True)

class AppleOpenSourceProjectsParser(html.parser.HTMLParser):
    def __init__(self, ProjName):
        # On creation of the class, create an array for the resulting
        # versions, and a variable for the project's name.
        self.Versions = []
        self.ProjName = ProjName

        # Initialise the base class.
        html.parser.HTMLParser.__init__(self)

    def handle_data(self, data):
        # When we get to the contents of a tag (i.e. 'data' in
        # <tag>data</tag>):

        match = re.search(r"^(?P<proj_ver>" + self.ProjName
                          + "-[\.\d]+)/$", data.strip())
        if match:
            self.Versions.append(match.group('proj_ver'))

    def feed(self, data):
        # Augment the existing feed() method by sorting the Versions list
        # by the value of each dictionary's 'full' key when done.

        html.parser.HTMLParser.feed(self, data)
        self.Versions = sorted(self.Versions,
                               key=distutils.version.LooseVersion,
                               reverse=True)

def GetMacOSVersions():
    # Get versions of software listed at https://opensource.apple.com/

    # Get the contents of https://opensource.apple.com/ , create an instance
    # of our AppleOpenSourceReleasesParser, feed the data from
    # https://opensource.apple.com/ into our parser, and return a list of
    # versions (In the form of a dictionary with the keys 'full' (for a
    # user-printable version string) and 'raw-id' (for the version string
    # used at https://opensource.apple.com/ )).
    AppleOpenSource = DLSoftware.\
                      DLOrUseLocalCopy('https://opensource.apple.com',
                                       'AppleOpenSource/index.html',
                                       'Apple Open Source Releases')

    macOSVersions = AppleOpenSourceReleasesParser()
    macOSVersions.feed(AppleOpenSource)

    return macOSVersions.Versions

def GetProjectVersions(Project):
    # Get versions of projects listed at
    # https://opensource.apple.com/source/Project/

    # Get the contents of https://opensourcr.apple.com/source/Project/ ,
    # create an instance of our AppleOpenSourceProjectParser, feed the data
    # from https://opensource.apple.com/source/Project/ into our parser, and
    # return a list of versions. ('full' and 'raw-id' (used in the macOS
    # versions parser above) are not need because they are the same.)
    AppleOpenSource = DLSoftware.\
                      DLOrUseLocalCopy(('https://opensource.apple.com/'
                                        + 'source/' + Project + '/'),
                                       ('AppleOpenSource/' + Project
                                        + '.html'),
                                       (Project + ' versions '
                                        + 'from Apple Open Source'))

    ProjectVersions = AppleOpenSourceProjectsParser(Project)
    ProjectVersions.feed(AppleOpenSource)

    return ProjectVersions.Versions
