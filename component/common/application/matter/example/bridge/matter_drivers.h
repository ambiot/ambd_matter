#pragma once

#include "matter_events.h"

#include <platform/CHIPDeviceLayer.h>

CHIP_ERROR matter_driver_bridge_light_init(void);
void matter_driver_bridge_endpoint_assign(void);
void matter_driver_bridge_setup_server(void);
void matter_driver_uplink_update_handler(AppEvent * event);
void matter_driver_downlink_update_handler(AppEvent *aEvent);

