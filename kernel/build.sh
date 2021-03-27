#!/bin/bash -eu

pushd ~/edk2
build
popd
make
~/osbook/devenv/run_qemu.sh ~/edk2/Build/MicatLoaderX64/DEBUG_CLANG38/X64/Loader.efi $HOME/micat-os/kernel/kernel.elf 
