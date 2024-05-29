#pragma once

#include <platform/CHIPDeviceLayer.h>

/**
 * @brief
 * This function is to start matter core related functions (server, platform manager)
 * Matter Platform (chip stack, event loop) will only be started at the first start
 */
CHIP_ERROR matter_core_start(void);

/**
 * @brief
 * This function is to stop matter server
 * Matter Platform will not be stopped in the function
 */
CHIP_ERROR matter_core_stop(void);

/**
 * @brief
 * This function returns true if matter server is still running, otherwise return false
 */
bool matter_core_server_is_running(void);
