#!/bin/bash  -eu

pushd ~/edk2
build
popd
cd ~/mikanos/kernel
make all
~/osbook/devenv/run_qemu.sh ~/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi $HOME/mikanos/kernel/kernel.elf 
