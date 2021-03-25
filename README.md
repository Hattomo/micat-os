# micat os
mikan + cat = micat os

## Build UEFI Boot Loader
```bash
cd $HOME/edk2
source edksetup.sh
build
~/osbook/devenv/run_qemu.sh Build/MicatLoaderX64/DEBUG_CLANG38/X64/Loader.efi
```
## Reference
- [mikan os](https://github.com/uchan-nos/mikanos)
- [mikan build](https://github.com/uchan-nos/mikanos-build)
