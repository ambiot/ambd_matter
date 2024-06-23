list (
    APPEND inc_path

    "${prj_root}/inc/inc_hp"

    "${sdk_root}/component/os"
    "${sdk_root}/component/os/freertos"
    "${sdk_root}/component/os/freertos/${freertos}/Source/include"
    "${sdk_root}/component/os/freertos/${freertos}/Source/portable/GCC/RTL8721D_HP/non_secure"
    "${sdk_root}/component/os/freertos/${freertos}/Source/portable/GCC/RTL8721D_HP/secure"

    "${sdk_root}/component/soc/realtek/amebad/cmsis"
    "${sdk_root}/component/soc/realtek/amebad/cmsis/device"
    "${sdk_root}/component/soc/realtek/amebad/cmsis-dsp/Source"
    "${sdk_root}/component/soc/realtek/amebad/fwlib/include"
    "${sdk_root}/component/soc/realtek/amebad/fwlib/rom_map_hp"
    "${sdk_root}/component/soc/realtek/amebad/app/monitor/include"
    "${sdk_root}/component/soc/realtek/amebad/app/xmodem"
    "${sdk_root}/component/soc/realtek/amebad/swlib/include"
    "${sdk_root}/component/soc/realtek/amebad/swlib/string"
    "${sdk_root}/component/soc/realtek/amebad/misc"
    "${sdk_root}/component/soc/realtek/amebad/swlib/os_dep/include"
    "${sdk_root}/component/soc/realtek/amebad/swlib/os_dep/../"

    "${sdk_root}/component/common/api"
    "${sdk_root}/component/common/api/platform"
    "${sdk_root}/component/common/api/wifi"
    "${sdk_root}/component/common/api/network"
    "${sdk_root}/component/common/api/network/include"
    "${sdk_root}/component/common/application/matter/application"
    "${sdk_root}/component/common/application/matter/protobuf"
    "${sdk_root}/component/common/application/matter/protobuf/nanopb"
    "${sdk_root}/component/common/audio"
    "${sdk_root}/component/common/test"
    "${sdk_root}/component/common/example"
    "${sdk_root}/component/common/utilities"
    "${sdk_root}/component/common/drivers/si"

#AUDIO
    "${sdk_root}/component/common/audio"
    "${sdk_root}/component/common/audio/faac/include"
    "${sdk_root}/component/common/audio/faac/libfaac"
    "${sdk_root}/component/common/audio/faac"
    "${sdk_root}/component/common/audio/haac"
    "${sdk_root}/component/common/audio/hmp3"
    "${sdk_root}/component/common/audio/g711"
    "${sdk_root}/component/common/audio/speex"
    "${sdk_root}/component/common/audio/speex/speex"
    "${sdk_root}/component/common/audio/fdk-aac"
    "${sdk_root}/component/common/audio/fdk-aac/libSYS/include"

#MMF
    "${sdk_root}/component/common/example/media_framework"
    "${sdk_root}/component/common/media"
    "${sdk_root}/component/common/media/samples"
    "${sdk_root}/component/common/media/mmfv2"
    "${sdk_root}/component/common/media/rtp_codec"

#WIFI
    "${sdk_root}/component/common/drivers/wlan/realtek/include"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/hci"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/osdep"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/hal"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/hal/phydm"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/hal/rtl8721d"
    "${sdk_root}/component/common/drivers/wlan/realtek/wlan_ram_map/rom"
    "${sdk_root}/component/common/drivers/wlan/realtek/src/core/option"
    "${sdk_root}/component/common/network"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/src/include"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/src/include/lwip"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/src/include/netif"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/port/realtek"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/port/realtek/freertos"
    "${sdk_root}/component/common/network/lwip/lwip_v2.1.2/port/realtek/include"
    "${sdk_root}/component/common/api"
    "${sdk_root}/component/common/api/at_cmd"
    "${sdk_root}/component/common/api/wifi/rtw_wpa_supplicant/src"
    "${sdk_root}/component/common/api/wifi/rtw_wpa_supplicant/src/crypto"
    "${sdk_root}/component/os/os_dep/include/"

#INIC
    "${sdk_root}/component/common/drivers/inic/rtl8721d"

#RTSP
    "${sdk_root}/component/common/network/rtsp"

#SSL
    "${sdk_root}/component/common/network/ssl/polarssl-1.3.8/include"
    "${sdk_root}/component/common/network/ssl/mbedtls-2.28.1/include"
    "${sdk_root}/component/common/network/ssl/ssl_ram_map/rom"

#MBEDTLS
    "${sdk_root}/component/common/application/matter"
    "${sdk_root}/component/common/application/matter/common/mbedtls"
    "${sdk_root}/component/common/application/matter/common/port"
    "${sdk_root}/component/common/application/matter/common/include"

#temp for git server code
    "${sdk_root}/component/common/mbed/targets/hal/rtl8721d/"
    "${sdk_root}/component/common/mbed/targets/hal/rtl8721d/include"
    "${sdk_root}/component/common/mbed/api/"
    "${sdk_root}/component/common/mbed/hal/"
    "${sdk_root}/component/common/mbed/hal_ext/"

    "${sdk_root}/component/common/file_system/fatfs/r0.10c/include"
    "${sdk_root}/component/common/file_system/fatfs"
    "${sdk_root}/component/common/file_system/ftl"
    "${sdk_root}/component/common/file_system/dct"

    "${sdk_root}/component/common/application/baidu/libduer-device/framework/core"
    "${sdk_root}/component/common/application/baidu/libduer-device/framework/include"
    "${sdk_root}/component/common/application/baidu/duerapp/include"

    "${sdk_root}/component/common/ui/emwin/emWinLibrary/include"
    "${sdk_root}/component/common/ui/emwin/Sample/rtl8721d/Config"
    "${sdk_root}/component/common/ui/emwin/Sample/rtl8721d/hal"

#BT config
    "${sdk_root}/component/common/bluetooth/realtek/sdk/example/ble_peripheral"
    "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_config"

)

if(CONFIG_BT_EN)
    list (
        APPEND inc_path
        "${sdk_root}/component/common/bluetooth/realtek/sdk"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/app"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/bluetooth/gap"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/bluetooth/gap/gap_lib"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/os"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/platform"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/bluetooth/profile"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/bluetooth/profile/client"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/bluetooth/profile/server"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/inc/stack"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/amebad/src"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/amebad/src/data_uart"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/amebad/src/hci"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/amebad/src/vendor_cmd"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/amebad/lib"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/board/common/inc"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/src/mcu/module/data_uart_cmd"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/ble_peripheral"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/ble_central"
        "${sdk_root}/component/common/application/matter/common/bluetooth/bt_matter_adapter"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/ble_scatternet"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_beacon"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_config"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_airsync_config"
        "${sdk_root}/component/common/bluetooth/realtek/../../application/airsync/1.0.4"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_breeze"
        "${sdk_root}/component/common/bluetooth/realtek/../../application/breeze/include"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_mesh_multiple_profile/provisioner_multiple_profile"
        "${sdk_root}/component/common/bluetooth/realtek/sdk/example/bt_mesh_multiple_profile/device_multiple_profile"
    )
endif()

