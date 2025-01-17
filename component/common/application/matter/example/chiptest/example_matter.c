#include <platform_opts.h>
#include <platform_stdlib.h>
#include "wifi_constants.h"
#include "wifi/wifi_conf.h"

extern void ChipTest(void);

static void example_matter_task_thread(void *pvParameters)
{
   while(!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE))) {
        //waiting for Wifi to be initialized
    }

    matter_timer_init();
    ChipTest();

    vTaskDelete(NULL);
    return;
}

void example_matter_task(void)
{
    if(xTaskCreate(example_matter_task_thread, ((const char*)"example_matter_task_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        printf("\n\r%s xTaskCreate(example_matter_task_thread) failed", __FUNCTION__);
}
