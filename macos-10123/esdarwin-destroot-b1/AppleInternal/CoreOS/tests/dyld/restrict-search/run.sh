#!/bin/sh
cd /AppleInternal/CoreOS/tests/dyld/restrict-search
./restrict-search-lc-find.exe
./restrict-search-lc-no-find.exe
./restrict-search-rpath-find.exe
./restrict-search-rpath-no-find.exe

