# Matter (previously CHIP) on AmebaD

## Get Ameba SDK & Matter SDK

    Tested on Ubuntu 20.04
    
Create a common directory for Ameba and Matter SDK

    mkdir dev
    
    cd dev

To check out this repository:

    git clone https://github.com/ambiot/ambd_matter.git

To check out Matter repository:

    git clone --recurse-submodules https://github.com/project-chip/connectedhomeip.git
    
Make sure ambz2_matter and connectedhomeip are on the same directory level

    dev/
	├── ambd_matter
	└── connectedhomeip

## Set Matter Build Environment 

    > Follow below guide to install prerequisites
    > https://github.com/project-chip/connectedhomeip/blob/master/docs/guides/BUILDING.md

    cd connectedhomeip
    
    git submodule sync

    git submodule update --init --recursive
    
    source scripts/bootstrap.sh

    source scripts/activate.sh

## Make project_lp

    cd sdk_amebad_v6.2C-RC/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp/
    
    make all

## Make Matter Libraries

    cd sdk_amebad_v6.2C-RC/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/
    
    make -C asdk lib_all
    
## Make project_hp

    in the same project_hp directory,
    
    make all

