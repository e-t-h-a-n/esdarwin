# ESDarwin macOS 10.12.3 destroot

## Important Information:

- This is in _very_ early stages!
- This doesn't contain the kernel extensions (`kexts`) needed to turn this into a virtual machine. (I'm working on a VM with some of the folks at [PureDarwin](https://github.com/PureDarwin/PureDarwin), though).
- I haven't made patches / documentation on how to build most of the projects here (open up a pull request or send an email to me at ethansherriff@hotmail.co.uk if you ever need anything).
- This has some missing projects / libraries in it, so not all applications will run correctly (expect lots of error messages from dyld): 


        dyld: Library not loaded... (/usr/lib/system/lib*.dylib)
            Referenced from: /an/application/you/are/trying/to/run *or* /usr/lib/libSystem.B.dylib
            Reason: image not found


- `Libsystem` is missing `CommonCrypto` and `coreTLS`, because they depened on `corecrypto`, which has lots of subcomponents missing, and is not _completely_ open source (i.e. the license only gives you 90 days to build and "internally deploy" `corecrypto` in your organisation - or something along those lines). 
- Some login-related libraries / projects are missing, so bash will say "I have no name!" instead of displaying your actual username.

## Compressed Libraries:

Some of the libraries here are too large for github to handle, so I compressed them with `xz`. If you are going to submit new binaries which are `100Mb+`, please ensure you pass the `-e` option to `xz`, as to make extracting quicker for users.

### The following libraries are compressed (with `xz`):

- `/usr/local/lib/loaderd/libc.a` (`.xz`)
- `/usr/local/lib/system/libc.a` (`.xz`)
- `/usr/local/lib/system/libc_debug.a` (`.xz`)

Currently, these are all static archives, so unless you are building some low-level system components (none of which rely on any of these, AFAIK), you will not need to extract these.

##### If you found any of my work helpful, credit is appreciated (not mandatory, though).