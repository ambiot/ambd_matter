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
Enable `CONFIG_EXAMPLE_MATTER` and `CONFIG_EXAMPLE_MATTER_LIGHT` in `platform_opts.h`.
Ensure that `CONFIG_EXAMPLE_MATTER_CHIPTEST` is disabled.

### PSRAM usage
Due to insufficient memory in SRAM, we will use the PSRAM for dynamic allocation.
To run this example without error, you need to enable PSRAM.
In `rtl8721dhp_intfcfg.c`, set the below configurations

    PSRAMCFG_TypeDef psram_dev_config = {
      .psram_dev_enable = TRUE,			//enable psram
	  .psram_dev_cal_enable = TRUE,			//enable psram calibration function
	  .psram_dev_retention = TRUE,
    }

### Setup the Build Environment
  
    cd connectedhomeip
    source scripts/activate.sh
  
### Build Matter Libraries

    cd ambz2_matter/component/common/application/matter/example/light
    make light
    
### Build the Final Firmware

    cd ambz2_matter/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make is_matter
    
### Flash the Image
Refer to this [guide](https://github.com/ambiot/ambz2_matter/blob/main/tools/AmebaZ2/Image_Tool_Linux/README.md) to flash the image with the Linux Image Tool

### Clean Matter Libraries

    cd ambz2_matter/component/common/application/matter/example/light
    make clean
