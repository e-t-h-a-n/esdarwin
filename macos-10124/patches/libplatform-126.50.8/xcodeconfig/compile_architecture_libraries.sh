#!/bin/sh

#  compile_architecture_libraries.sh
#  libplatform
#
#  Created by Ethan on 12/03/2017.
#  Copyright © 2017 Ethan Sherriff. All rights reserved.
#  This script, along with my other patches to libplatform
#  are made available under both the Apple Public Source
#  License Version 2, and the MIT License.

#!/usr/bin/env bash

set -x
set -e

CC="$(xcrun --sdk ${SDKROOT} --find clang)"
CFLAGS="-I$SRCROOT/internal -I$SDKROOT/System/Library/Frameworks/System.Framework/PrivateHeaders -DVARIANT_${CURRENT_VARIANT} -DVARIANT=${CURRENT_VARIANT} -fdollars-in-identifiers"

PRODUCT="$1"

for define in $GCC_PREPROCESSOR_MACROS; do
    CFLAGS+="-D${define}"
done

if [[ $ACTION = "clean" ]]; then
rm -rf "${OBJROOT}/*"
fi

if [[ " $ARCHS " = *" arm64 "* ]]; then
    ARM64=$(find "$SRCROOT/src" -path "*/arm64/*.s")
    mkdir -p "${OBJROOT}/arm64"
    for srcfile in $ARM64; do
        FileNameAndPathWithExtension="${srcfile##${SRCROOT}\/src/}"
        FileNameWithExtension="${srcfile##*/}"
        FilePath="${FileNameAndPathWithExtension%/*}"
        OutFileName="$(echo $FilePath | sed 's/\//-/g')-${FileNameWithExtension%.*}"
        "$CC" -c -arch arm64 $CFLAGS "$srcfile" -o "$OBJROOT"/arm64/"${OutFileName}".o
        ar crsu "$OBJROOT"/libplatform-"$PRODUCT"-arm64.a "$OBJROOT"/arm64/*.o
    done
fi


if [[ " $ARCHS " = *" arm "* ]]; then
    ARM=$(find "$SRCROOT/src" -path "*/arm/*.s")
    mkdir -p "${OBJROOT}/arm"
    for srcfile in $ARM; do
        FileNameAndPathWithExtension="${srcfile##${SRCROOT}\/src/}"
        FileNameWithExtension="${srcfile##*/}"
        FilePath="${FileNameAndPathWithExtension%/*}"
        OutFileName="$(echo $FilePath | sed 's/\//-/g')-${FileNameWithExtension%.*}"
        "$CC" -c -arch armv7 -arch armv7s -armv7k $CFLAGS "$srcfile" -o "$OBJROOT"/arm/"${OutFileName}".o
        ar crsu "$OBJROOT"/libplatform-"$PRODUCT"-arm.a "$OBJROOT"/arm/*.o
    done
fi



if [[ " $ARCHS " = *" i386 "* ]]; then
    I386=$(find "$SRCROOT/src" -path "*/i386/*.s")
    mkdir -p "${OBJROOT}/i386"
    for srcfile in $I386; do
        FileNameAndPathWithExtension="${srcfile##${SRCROOT}\/src/}"
        FileNameWithExtension="${srcfile##*/}"
        FilePath="${FileNameAndPathWithExtension%/*}"
        OutFileName="$(echo $FilePath | sed 's/\//-/g')-${FileNameWithExtension%.*}"
        "$CC" -c -arch i386 $CFLAGS "$srcfile" -o "$OBJROOT"/i386/"${OutFileName}".o
        ar crsu "$OBJROOT"/libplatform-"$PRODUCT"-i386.a "$OBJROOT"/i386/*.o
    done
fi


if [[ " $ARCHS " = *" x86_64 "* ]]; then
    X86_64=$(find "$SRCROOT/src" -path "*/x86_64/*.s")
    mkdir -p "${OBJROOT}/x86_64"
    for srcfile in $X86_64; do
        FileNameAndPathWithExtension="${srcfile##${SRCROOT}\/src/}"
        FileNameWithExtension="${srcfile##*/}"
        FilePath="${FileNameAndPathWithExtension%/*}"
        OutFileName="$(echo $FilePath | sed 's/\//-/g')-${FileNameWithExtension%.*}"
        "$CC" -c -arch x86_64 $CFLAGS "$srcfile" -o "$OBJROOT"/x86_64/"${OutFileName}".o
        ar crsu "$OBJROOT"/libplatform-"$PRODUCT"-x86_64.a "$OBJROOT"/x86_64/*.o
    done
fi
