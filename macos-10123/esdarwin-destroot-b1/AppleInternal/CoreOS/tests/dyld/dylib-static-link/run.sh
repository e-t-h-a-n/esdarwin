#!/bin/sh
cd /AppleInternal/CoreOS/tests/dyld/dylib-static-link
./dylib-static-present.exe
NOCR_TEST_NAME="dylib-static-link missing" nocr -require_crash ./dylib-static-missing.exe

