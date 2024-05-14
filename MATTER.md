# Matter (previously CHIP) on AmebaD

## Reminder

### For v1.3.0.0 onwards, all-clusters-app.zap location change

If you need to change all-clusters-app.zap, please change it in the following directory:

	component/common/application/matter/example/chiptest/all-clusters-app.zap

This is because we have added all files required for all supported clusters in `component/common/application/matter/project/amebad/make/chip_main/all_clusters_app/Makefile`, while the default all-clusters-app.zap in connectedhomeip does not include some clusters supported by Ameba. Therefore, build errors occur.

The only solution is to add Ameba's all-clusters-app.zap. 

In `component/common/application/matter/project/amebad/Makefile`, the default all-clusters-app.zap in connectedhomeip will be replaced by Ameba's all-clusters-app.zap

	@cp $(MATTER_DIR)/example/chiptest/all-clusters-app.zap $(ALL_CLUSTERS_ZAP)

## Get Ameba SDK & Matter SDK

    Tested on Ubuntu 22.04
    
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

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp/
    
    make all

## Make Matter Libraries

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp/
    
    make -C asdk all_clusters
    
## Make project_hp

    in the same project_hp directory,
    
    make all

