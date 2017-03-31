# ESDarwin macOS 10.12.3 destroot

## Important Information:

- This is in _very_ early stages!
- Some of the `dylib`s have incorrect versions, I'm correcting this now though.
- This doesn't contain the kernel extensions (`kexts`) needed to turn this into a virtual machine. (I'll work on this soon, though).
- I haven't released patches / documentation on how to build most of the projects here (open up a pull request or send an email to me at ethansherriff@hotmail.co.uk if you ever need anything).
- When you exit a program it ends in a segmentation fault (yeah, I **really** need to debug this, but it'll be fine for now).
- Lots of system libraries depend on a couple of "stubs". I only made these to please dyld and "work around" some "image not found" errors, so I will (sooner or later) remove the links to these stubs by editing the Xcode projects. Generating the stub dylibs is done by using the `generate-stub-libraries` script under `useful-scripts/`, if you're interested :).

## Compressed Libraries:

Some of the libraries here are too large for github to handle, so I compressed them with `xz`. If you are going to submit new binaries which are `100Mb+`, please ensure you pass the `-e` option to `xz`, as to make extracting quicker for users.

### The following libraries are compressed (with `xz`):

- `/usr/local/lib/loaderd/libc.a` (`.xz`)
- `/usr/local/lib/system/libc.a` (`.xz`)
- `/usr/local/lib/system/libc_debug.a` (`.xz`)

Currently, these are all static archives, so unless you are building some low-level system components (none of which rely on any of these, AFAIK), you will not need to extract these.

##### If you found any of my work helpful, credit is appreciated (not mandatory, though).