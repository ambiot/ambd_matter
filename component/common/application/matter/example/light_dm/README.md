# Lighting-app using Ameba Data Model Example
This example is an implementation of the *Dimmable Light* device type using the *Ameba Data Model*. You will need an LED and a button.

| Peripheral | Pin |
| ----------- | ----------- |
| LED | PA_23 |
| Button | PA_17 |

## Ameba Data Model
This example demonstrates adding and removing endpoints dynamically using the *Ameba Data Model*.
A `Root Node` endpoint will be created on Endpoint0, and a `Dimmable Light` endpoint on Endpoint1.
After a 20 second delay, another `Dimmable Light` enpdoint will be added on Endpoint2.
After another 20 second delay, the `Dimmable Light` endpoint on Endpoint2 will be removed.

## How to build

### Configurations
Enable `CONFIG_EXAMPLE_MATTER` and `CONFIG_EXAMPLE_MATTER_LIGHT` in `platform_opts_matter.h`.
Ensure that `CONFIG_EXAMPLE_MATTER_CHIPTEST` is disabled.

### Setup the Build Environment
  
    cd connectedhomeip
    source scripts/activate.sh
  
### Build Project LP

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp/
    make all

### Build Matter Libraries

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/
    make -C asdk/ light_dm
    
### Build the Final Firmware

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/
    make all
    
### Flash the Image
Refer to this [guide](https://github.com/ambiot/ambd_matter/blob/main/tools/AmebaD/Image_Tool_Linux/README.txt) to flash the image with the Linux Image Tool

### Clean Matter Libraries

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/
    make clean
