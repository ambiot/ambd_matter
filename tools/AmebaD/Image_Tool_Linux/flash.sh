#!/usr/bin/env bash

# Usage
# ./flash.sh <Device Port> <Path to Output Dir>
# ./flash.sh /dev/ttyUSB0 /path/to/output

if [ -z "$1" ]
  then
    echo "No device port provided"
    exit
fi

if [ -z "$2" ]
  then
    echo "No output directory provided"
    exit
fi

SDK_ROOT_DIR=$PWD/../../..
OUTPUT_DIR=$2
BOOT_DIR=$OUTPUT_DIR/asdk/bootloader
IMAGE_DIR=$OUTPUT_DIR/asdk/image
rm -rf log* Image_All.bin*
sudo ./AmebaD_ImageTool -set chip AmebaD
sudo ./AmebaD_ImageTool -add device $1
sudo ./AmebaD_ImageTool -set baudrate 1500000
sudo ./AmebaD_ImageTool -combine $BOOT_DIR/km0_boot_all.bin 0x0000 $BOOT_DIR/km4_boot_all.bin 0x4000 $IMAGE_DIR/km0_km4_image2.bin 0x6000
sudo ./AmebaD_ImageTool -set image $PWD/Image_All.bin
sudo ./AmebaD_ImageTool -set address 0x08000000
sudo ./AmebaD_ImageTool -show
read -p "Check if the settings are correct, then enter UART DOWNLOAD mode
1) Push the UART DOWNLOAD button and keep it pressed.
2) Re-power on the board or press the Reset button.
3) Release the UART DOWNLOAD button.
Once AmebaD entered UART Download mode, press Enter to continue"
sudo ./AmebaD_ImageTool -download
