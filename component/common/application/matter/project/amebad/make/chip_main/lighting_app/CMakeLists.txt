cmake_minimum_required(VERSION 3.6)

# Define the name of the project
project(chip_main_rpc)

message("Building RPC: ${CMAKE_CURRENT_SOURCE_DIR}")

set (sdk_root "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../..")
set (build_root "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set (prj_root "${sdk_root}/project/realtek_amebaD_va0_example")

# Define the chip directory and pigweed directory
set(chip_dir "${sdk_root}/third_party/connectedhomeip")
set(chip_dir_out "${sdk_root}/third_party/connectedhomeip/examples/lighting-app/ameba/build/chip")
set(pigweed_dir "${chip_dir}/third_party/pigweed/repo")
set(chip_dir_output "${build_root}/chip_rpc")
set(chip_main_rpc chip_main_rpc)
set(list_chip_main_rpc_sources chip_main_rpc_sources)

set(freertos "freertos_v10.2.0")
set(lwip "lwip_v2.1.2")

set(CONFIG_BT_EN ON)

include(${build_root}/includepath.cmake)
include(${pigweed_dir}/pw_build/pigweed.cmake)
include(${pigweed_dir}/pw_protobuf_compiler/proto.cmake)
include(${pigweed_dir}/pw_assert/backend.cmake)
include(${pigweed_dir}/pw_log/backend.cmake)
include(${pigweed_dir}/pw_sys_io/backend.cmake)
include(${pigweed_dir}/pw_trace/backend.cmake)

set(dir_pw_third_party_nanopb "${chip_dir}/third_party/nanopb/repo" CACHE STRING "" FORCE)

pw_set_module_config(pw_rpc_CONFIG pw_rpc.disable_global_mutex_config)
pw_set_backend(pw_log pw_log_basic)
pw_set_backend(pw_assert.check pw_assert_log.check_backend)
pw_set_backend(pw_assert.assert pw_assert.assert_compatibility_backend)
pw_set_backend(pw_sys_io pw_sys_io.ameba)
pw_set_backend(pw_trace pw_trace_tokenized)

#Add another directory to your build. Which process another CMakeLists.txt directory
add_subdirectory(${chip_dir}/third_party/pigweed/repo ${chip_dir_output}/out/pigweed)
add_subdirectory(${chip_dir}/third_party/nanopb/repo ${chip_dir_output}/out/nanopb)
add_subdirectory(${chip_dir}/examples/platform/ameba/pw_sys_io ${chip_dir_output}/out/pw_sys_io)

pw_proto_library(attributes_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/attributes_service.proto
  INPUTS
    ${chip_dir}/examples/common/pigweed/protos/attributes_service.options
  PREFIX
    attributes_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(button_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/button_service.proto
  PREFIX
    button_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(descriptor_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/descriptor_service.proto
  PREFIX
    descriptor_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(device_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/device_service.proto
  INPUTS
    ${chip_dir}/examples/common/pigweed/protos/device_service.options
  PREFIX
    device_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(lighting_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/lighting_service.proto
  PREFIX
    lighting_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(locking_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/locking_service.proto
  PREFIX
    locking_service
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
  DEPS
    pw_protobuf.common_proto
)

pw_proto_library(wifi_service
  SOURCES
    ${chip_dir}/examples/common/pigweed/protos/wifi_service.proto
  INPUTS
    ${chip_dir}/examples/common/pigweed/protos/wifi_service.options
  PREFIX
    wifi_service
  DEPS
    pw_protobuf.common_proto
  STRIP_PREFIX
    ${chip_dir}/examples/common/pigweed/protos
)

list(
    APPEND ${list_chip_main_rpc_sources}
    #rpc
    ${chip_dir}/examples/platform/ameba/PigweedLogger.cpp
    ${chip_dir}/examples/platform/ameba/Rpc.cpp
    ${chip_dir}/examples/common/pigweed/RpcService.cpp
    ${chip_dir}/examples/common/pigweed/ameba/PigweedLoggerMutex.cpp
    ${chip_dir}/examples/platform/ameba/pw_sys_io/sys_io_ameba.cc
)

add_library(
    ${chip_main_rpc}
    STATIC
    ${chip_main_rpc_sources}
)

target_include_directories(
    chip_main_rpc
    PUBLIC
    ${inc_path}
    ${chip_dir}/zzz_generated/app-common
    ${chip_dir}/zzz_generated/lighting-app
    ${chip_dir}/zzz_generated/lighting-app/zap-generated
    ${chip_dir}/examples/lighting-app/lighting-common
    ${chip_dir}/examples/lighting-app/lighting-common/include
    ${chip_dir}/examples/lighting-app/ameba/main/include
    ${chip_dir_out}/codegen
    ${chip_dir_out}/gen/include
    ${chip_dir}/examples/platform/ameba
    ${chip_dir}/examples/platform/ameba/route_hook
    ${chip_dir}/examples/platform/ameba/pw_sys_io/public
    ${chip_dir}/examples/providers
    ${chip_dir}/examples/common
    ${chip_dir}/examples/common/pigweed
    ${chip_dir}/examples/common/pigweed/ameba
    ${chip_dir}/src
    ${chip_dir}/src/app/
    ${chip_dir}/src/app/util/
    ${chip_dir}/src/app/server/
    ${chip_dir}/src/controller/data_model
    ${chip_dir}/src/include/
    ${chip_dir}/src/lib
    ${chip_dir}/src/lib/support
    ${chip_dir}/third_party/nlassert/repo/include/
    ${chip_dir}/third_party/nlio/repo/include/
    ${chip_dir}/third_party/nlunit-test/repo/src
)

target_link_libraries(chip_main_rpc PUBLIC
    attributes_service.nanopb_rpc
    button_service.nanopb_rpc
    descriptor_service.nanopb_rpc
    device_service.nanopb_rpc
    lighting_service.nanopb_rpc
    locking_service.nanopb_rpc
    wifi_service.nanopb_rpc
    pw_checksum
    pw_hdlc
    pw_log
    pw_rpc.server
    pw_sys_io
    pw_trace_tokenized
    pw_trace_tokenized.trace_buffer
    pw_trace_tokenized.rpc_service
    pw_trace_tokenized.protos.nanopb_rpc
    pw_sys_io_default_putget_bytes
    pw_sys_io_facade
    PwRpc
)

link_directories(
    ${chip_dir_out}/lib
)

# Set compile flags and options
list(
    APPEND chip_main_rpc_flags

	-DCONFIG_PLATFORM_8721D
    -DINET_CONFIG_ENABLE_IPV4=0
    -DCHIP_PROJECT=1
    -DCHIP_DEVICE_LAYER_TARGET=Ameba
    -DCHIP_HAVE_CONFIG_H
    -DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>
    -DPW_RPC_ATTRIBUTE_SERVICE=1
    -DPW_RPC_BUTTON_SERVICE=1
    -DPW_RPC_DESCRIPTOR_SERVICE=1
    -DPW_RPC_DEVICE_SERVICE=1
    -DPW_RPC_LIGHTING_SERVICE=1
    -DPW_RPC_LOCKING_SERVICE=1
    -DCONFIG_ENABLE_PW_RPC=1
)

list(
    APPEND chip_main_rpc_cpp_flags
    -Wno-unused-parameter
    -Wconversion
    -std=c++17
    -fno-rtti
)

target_compile_definitions(chip_main_rpc PRIVATE ${chip_main_rpc_flags})
target_compile_options(chip_main_rpc PRIVATE ${chip_main_rpc_cpp_flags})

# Set the default install prefix to a user-writable directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install path" FORCE)
endif()

# Install the library and headers
install(TARGETS chip_main_rpc
        EXPORT chip_main_rpcTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

# Install the include directories
install(DIRECTORY ${chip_dir}/examples/platform/ameba
                 ${chip_dir}/examples/platform/ameba/pw_sys_io/public
                 ${chip_dir}/examples/common
                 ${chip_dir}/examples/common/pigweed
                 ${chip_dir}/examples/common/pigweed/ameba
                 ${chip_dir}/src
                 ${chip_dir}/src/lib/support
                 ${pigweed_dir}/pw_rpc/nanopb/public
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
