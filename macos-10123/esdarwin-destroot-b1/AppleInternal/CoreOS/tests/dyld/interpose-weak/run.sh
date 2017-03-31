#!/bin/sh
cd /AppleInternal/CoreOS/tests/dyld/interpose-weak
DYLD_INSERT_LIBRARIES=libinterposer.dylib   ./interpose-weak-present.exe
DYLD_INSERT_LIBRARIES=libinterposer2.dylib  ./interpose-weak-missing.exe

