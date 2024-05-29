/*
 * AT Command for Matter
*/
#include <platform_stdlib.h>
#include <platform_opts.h>

#include <sys_api.h>
#include "log_service.h"
extern u32 deinitPref(void);
#if MATTER_OTA_REQUESTOR_APP
extern void amebaQueryImageCmdHandler();
extern void amebaApplyUpdateCmdHandler();
#endif

// Queue for matter shell
QueueHandle_t shell_queue;

void fATchipapp(void *arg)
{
	/* To avoid gcc warnings */
	( void ) arg;

	printf("xPortGetTotalHeapSize = %d \n",xPortGetTotalHeapSize());
	printf("xPortGetFreeHeapSize = %d \n",xPortGetFreeHeapSize());
	printf("xPortGetMinimumEverFreeHeapSize = %d \n",xPortGetMinimumEverFreeHeapSize());

	deinitPref();

#if CONFIG_EXAMPLE_WLAN_FAST_CONNECT
	Erase_Fastconnect_data();
	printf("Erased Fast Connect data\r\n");
#endif

	AT_PRINTK("[ATM$]: _AT_SYSTEM_TEST_");
	wifi_disconnect();
	sys_reset();
}

void fATchipapp1(void *arg)
{
#ifdef MATTER_OTA_REQUESTOR_APP
	printf("Calling amebaQueryImageCmdHandler\r\n");
	amebaQueryImageCmdHandler();
#endif
}

void fATchipapp2(void *arg)
{
	(void) arg;
#ifdef MATTER_OTA_REQUESTOR_APP
	printf("Chip Test: amebaApplyUpdateCmdHandler\r\n");

	amebaApplyUpdateCmdHandler();
#endif
}

__weak void MatterCoreStatusCommandHandler(void) 
{
	printf("MatterCoreStatusCommandHandler() not implemented\r\n");
}

__weak void MatterCoreStartCommandHandler(void) 
{
	printf("MatterCoreStartCommandHandler() not implemented\r\n");
}

__weak void MatterCoreStopCommandHandler(void) 
{
	printf("MatterCoreStopCommandHandler() not implemented\r\n");
}

void fATmattershell(void *arg)
{
    if (arg != NULL)
    {
        if(strcmp((const char *) arg, "status") == 0)
        {
            MatterCoreStatusCommandHandler();
        }
        else if(strcmp((const char *) arg, "start") == 0)
        {
            MatterCoreStartCommandHandler();
        }
        else if(strcmp((const char *) arg, "stop") == 0)
        {
            MatterCoreStopCommandHandler();
        }
        else
        {
            xQueueSend(shell_queue, arg, pdMS_TO_TICKS(10));
        }
    }
    else
    {
        printf("%s\n%s\n%s\n%s\n%s\r\n",
            "No arguments provided for matter shell",
            "ATMS=status to check matter server status",
            "ATMS=start  to turn on matter server",
            "ATMS=stop   to turn off matter server",
            "ATMS=help   to check built in matter commands while matter server is on");
    } 
}

log_item_t at_matter_items[] = {
#ifndef CONFIG_INIC_NO_FLASH
#if ATCMD_VER == ATVER_1
    {"ATM$", fATchipapp, {NULL,NULL}},
    {"ATM%", fATchipapp1, {NULL, NULL}},
    {"ATM^", fATchipapp2, {NULL, NULL}},
    {"ATMS", fATmattershell, {NULL, NULL}},
#endif // end of #if ATCMD_VER == ATVER_1
#endif
};

void at_matter_init(void)
{
    shell_queue = xQueueCreate(3, 256); // backlog 3 commands max
	log_service_add_table(at_matter_items, sizeof(at_matter_items)/sizeof(at_matter_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_matter_init);
#endif
