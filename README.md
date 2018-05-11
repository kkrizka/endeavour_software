# Endeavour Test Firmware

Software for controlling the [endeavour_master firmware block](https://github.com/kkrizka/endeavour_firmware) on a Zynq FPGA. Communication with the device is done using the userspace I/O kernel module.

## Compilation
If using [PetaLinux](https://www.xilinx.com/products/design-tools/embedded-software/petalinux-sdk.html), make sure that have the build tools and CMake installed. To enable the [CMake Yocto recipe](https://github.com/openembedded/openembedded-core/tree/master/meta/recipes-devtools/cmake), append the following at the end of `./build/misc/rootfs_config/Kconfig.user`.
```
menu "user packages " 
config cmake  
         bool "cmake"
         help
endmenu
```

Enable the following packages when running `petalinux-config -c rootfs`.
```
-> Filesystem Packages
  -> misc
    -> [*] packagegroup-core-buildessential
-> user packages
  -> [*] cmake
```

The Endeavour software can then be compiled directly on the ARM core.
```
git clone https://github.com/kkrizka/endeavour_software.git
cd endeavour_software
mkdir build
cd build
cmake ..
make
```

Several useful tools will are available in the `bin/` directory.

