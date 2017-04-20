# libcoreservices-41.4

This is a small implementation of Apple's `libcoreservices` project, which contains `libsystem_coreservices.dylib`.

The code contains [old parts of Apple's `Libc`] (https://opensource.apple.com/source/Libc/Libc-997.90.3/gen/NSSystemDirectories.c)(`NSSystemDirectories.c` from `Libc-997.90.3`, licensed under the Apple Public Source License / APSL) and some [wrapper code](https://github.com/darlinghq/darling/tree/master/src/libsystem_coreservices) (`dirhelper.c` and `sysdir.c`) from the [Darling Project](https://darlinghq.org) which is licensed under the GNU General Public License (GPLv3). The Xcode project was created by me and is released in the public domain.