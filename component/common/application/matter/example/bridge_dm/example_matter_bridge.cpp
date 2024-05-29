#include "FreeRTOS.h"
#include "task.h"
#include "platform/platform_stdlib.h"
#include "basic_types.h"
#include "platform_opts.h"
#include "section_config.h"
#include "wifi_constants.h"
#include "wifi/wifi_conf.h"
#include "chip_porting.h"
#include "matter_core.h"
#include "matter_data_model.h"
#include "matter_data_model_presets.h"
#include "matter_drivers.h"
#include "matter_interaction.h"
#include "bridge_dm_driver.h"

#include <app/ConcreteAttributePath.h>
#include <app/reporting/reporting.h>
#include <app/util/attribute-storage.h>

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>

using namespace ::chip;
using namespace ::chip::DeviceLayer;
using namespace ::chip::Platform;
using namespace ::chip::app::Clusters;

MatterBridge bridge;
Node& node = Node::getInstance();

EmberAfDeviceType gBridgedOnOffDeviceTypes[] = {
    { DEVICE_TYPE_LO_ON_OFF_LIGHT, DEVICE_VERSION_DEFAULT },
    { DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT },
};

static void example_matter_bridge_task(void *pvParameters)
{
    while(!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE))) {
        vTaskDelay(500);
    }

    ChipLogProgress(DeviceLayer, "\nBridge Dynamic Endpoint example!\n");

    CHIP_ERROR err = CHIP_NO_ERROR;

    initPref();     // init NVS

    err = matter_driver_bridge_light_init();
    if (err != CHIP_NO_ERROR)
        ChipLogProgress(DeviceLayer, "matter_driver_bridge_light_init failed!\n");

    err = matter_core_start();
    if (err != CHIP_NO_ERROR)
        ChipLogProgress(DeviceLayer, "matter_core_start failed!\n");

    err = matter_interaction_start_downlink();
    if (err != CHIP_NO_ERROR)
        ChipLogProgress(DeviceLayer, "matter_interaction_start_downlink failed!\n");

    err = matter_interaction_start_uplink();
    if (err != CHIP_NO_ERROR)
        ChipLogProgress(DeviceLayer, "matter_interaction_start_uplink failed!\n");

    vTaskDelay(1000);

    bridge.Init(node);

    ChipLogProgress(DeviceLayer, "Add dimmable lights");
    for (int i = 0; i < CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT - 2; i++) //adding endpoints 2 to 19
    {
        ChipLogProgress(DeviceLayer, "Add dimmable lights [Endpoint 0x%x]", node.getNextEndpointId());
        bridge.addBridgedEndpoint(&Presets::Endpoints::matter_dimmable_light_endpoint, Span<const EmberAfDeviceType>(gBridgedOnOffDeviceTypes));
    }

    if(xTaskCreate(matter_customer_bridge_code, ((const char*)"matter_customer_bridge_code"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        printf("\n\r%s xTaskCreate(matter_customer_bridge_code) failed\n", __FUNCTION__);

    ChipLogProgress(DeviceLayer, "60 seconds until all lights removed\n\n");
    vTaskDelay(60000);
    ChipLogProgress(DeviceLayer, "Removing All Lights");
    for (int i = 1; i <= CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT - 2; i++) //removing endpoints 19 to 2
    {
        uint16_t epToBeRemoved = node.getNextEndpointId() - i;
        ChipLogProgress(DeviceLayer, "Removing Endpoint 0x%x", epToBeRemoved);
        bridge.removeBridgedEndpoint(epToBeRemoved);
    }

    vTaskDelete(NULL);
}

extern "C" void example_matter_bridge(void)
{
    if(xTaskCreate(example_matter_bridge_task, ((const char*)"example_matter_task_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        ChipLogProgress(DeviceLayer, "\n\r%s xTaskCreate(example_matter_light) failed", __FUNCTION__);
}
