#!/usr/bin/env python3.6

# psuedo-code
def __testing__PrepareSDKs(RawMacOSVersion):
    SDKFolder = GetSDKFolder()
    CurrentSDK = ''
    for SDK in SDKFolder:
        SettingsPlist = open(SDK + '/SDKSettings.plist')
        if SettingsPlist.hasValue(RawMacOSVersion.MajorAndMinor):
            CurrentSDK = SDK
            break
    if CurrentSDK is not '':
        return CurrentSDK
    else:
        raise NoSDKsForBuildError

def PrepareSDKs(RawMacOSVersion):
    pass
