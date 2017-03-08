#!/usr/bin/env python3.6

import argparse

# Create an argument parser.
parser = argparse.ArgumentParser(description="Create a bootable Darwin ISO.")

# Add our arguments
parser.add_argument('-C', '--no-caches', action='store_true',
                    help="Don't use our locally cached copies of "
                    + "Apple Open Source in the event of being unable to "
                    + "connect to the internet.")
parser.add_argument('-d', '--dl-only', action='store_true',
                    help="Only diwnload the tarballs and then exit")
parser.add_argument('-i', '--info', action='store_true',
                    help="Only get build information, then exit.")
parser.add_argument('-q', '--quiet', action='count', default=0,
                    help="Print less output. Use once to supress errors, "
                    + "and twice to supress warnings. Use 3 times to supress "
                    + "successes as well. We define a warning as "
                    + "an error that we can (possibly) recover from. You "
                    + "cannot supress errors using this flag.")

# Parse the arguments passed to out program at runtime, and store them in a
# dict.
args = vars(parser.parse_args())

# Some Configuration variables:

#FilesSite = 'https://github.com/darwinbuilder/darwinbuilder-files.git/'
FilesSite = 'http://localhost/darwinbuilder-files/'

PlistSite = lambda macOSVersion: (FilesSite + 'releases/' + macOSVersion
                                    + '.tobuild.plist')

SDKFolder = '/Applications/Xcode.app/Contents/Developer/' + \
            'Platforms/MacOSX.platform/Developer/SDKs'

# Define some escape sequences for ECMA-048 SGR colour codes.
# (These change the colour of the text printed to the terminal.)

# Font styles, display modes, etc...

Reset           = '\033[0m'
Bold            = '\033[1m'
Italics         = '\033[3m'
Underlined      = '\033[4m'
SlowBlink       = '\033[5m'
FastBlink       = '\033[6m' # Doesn't work on macOS's Terminal.app
Negative        = '\033[7m'
Concelaed       = '\033[8m'
CrossedOut      = '\033[9m'

# Foreground colours:

BlackFG         = '\033[30m'
RedFG           = '\033[31m'
GreenFG         = '\033[32m'
YellowFG        = '\033[33m'
BlueFG          = '\033[34m'
MagentaFG       = '\033[35m'
CyanFG          = '\033[36m'
WhiteFG         = '\033[37m'

# Bright foreground colours:

GreyFG          = '\033[90m'
BrightRedFG     = '\033[91m'
BrightGreenFG   = '\033[92m'
BrightYellowFG  = '\033[93m'
BrightBlueFG    = '\033[94m'
BrightMagentaFG = '\033[95m'
BrightCyanFG    = '\033[96m'
BrightWhiteFG   = '\033[97m'

# Background colours:

BlackBG         = '\033[40m'
RedBG           = '\033[41m'
GreenBG         = '\033[42m'
YellowBG        = '\033[43m'
BlueBG          = '\033[44m'
MagentaBG       = '\033[45m'
CyanBG          = '\033[46m'
WhiteBG         = '\033[47m'

# Bright background colours:

GreyBG          = '\033[100m'
BrightRedBG     = '\033[101m'
BrightGreenBG   = '\033[102m'
BrightYellowBG  = '\033[103m'
BrightBlueBG    = '\033[104m'
BrightMagentaBG = '\033[105m'
BrightCyanBG    = '\033[106m'
BrightWhiteBG   = '\033[107m'

# Now lets define some statuses for logging:

Info    = Bold + BrightCyanFG + "[INFO]:" + Reset + "    "
Warning = Bold + BrightYellowFG + "[WARNING]:" + Reset + " "
Success = Bold + BrightGreenFG + "[SUCCESS]:" + Reset + " "
Error   = Bold + BrightRedFG + "[ERROR]:" + Reset + "   "
Indent  = "           "

InlineInfo = lambda message: BrightWhiteFG + BrightBlueBG + message + Reset

# Our logging function.

def Log(status, message):
    # Convert the first arguent from a short string to our colour-coded
    # strings.
    if status == 'Info':
        status = Info
    elif status == 'Warning':
        status = Warning
    elif status == 'Success':
        status = Success
    elif status == 'Error':
        status = Error
    elif status == 'Indent':
        status = Indent
    else:
        # The status given to us has to be either 'Info', 'Warning', 'Success',
        # 'Error' or 'Indent'.
        raise ValueError("Status must be one of: 'Info', 'Warning', "
                         + "'Success', 'Error', or 'Indent'.")

    # Print in accordance with the '--quiet' flag.
    if args['quiet'] == 0:
        print(status, message)
    elif (args['quiet'] == 1) and (status != Info):
        print(status, message)
    elif (args['quiet'] == 2) and (status != Info and status != Warning):
        print(status, message)
    elif (args['quiet'] >= 3) and (status != Info and status != Warning
                                   and status != Success):
        print(status, message) # Only errors

