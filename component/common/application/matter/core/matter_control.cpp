/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "platform_opts_matter.h"
#include "matter_control.h"
#include "matter_core.h"
#include "matter_interaction.h"
#include "matter_prov.h"

#include "app/server/Server.h"
#include "platform/CHIPDeviceLayer.h"
#include <lib/support/CodeUtils.h>

#if defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)
#include "lib/shell/Engine.h"
#include "lib/shell/commands/Help.h"
#endif // defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)

using namespace chip;
using namespace chip::app;

#if defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)
using Shell::Engine;
using Shell::shell_command_t;
using Shell::streamer_get;
using Shell::streamer_printf;

Engine sShellMatterProvisioningSubCommands;
#endif // defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)

namespace {
#if defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)

/********************************************************
 * Matter Core shell functions, controlled by Ameba Shell
 *********************************************************/

extern "C" void MatterCoreStatusCommandHandler()
{
    if (matter_core_server_is_running())
    {
        ChipLogProgress(DeviceLayer, "Matter device is running!");
    }
    else
    {
        ChipLogProgress(DeviceLayer, "Matter device is not running!");
    }
}

extern "C" void MatterCoreStartCommandHandler()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if(matter_core_server_is_running())
    {
        ChipLogProgress(DeviceLayer, "Matter device is already started!");
    }
    else
    {
        err = matter_core_start();
        if (err != CHIP_NO_ERROR)
            ChipLogProgress(DeviceLayer, "matter_core_start failed!\n");

#if !(defined(CONFIG_EXAMPLE_MATTER_AIRCON) && CONFIG_EXAMPLE_MATTER_AIRCON) // aircon example does not include downlink
        err = matter_interaction_start_downlink();
        if (err != CHIP_NO_ERROR)
            ChipLogProgress(DeviceLayer, "matter_interaction_start_downlink failed!\n");
#endif

        err = matter_interaction_start_uplink();
        if (err != CHIP_NO_ERROR)
            ChipLogProgress(DeviceLayer, "matter_interaction_start_uplink failed!\n");
    }
}

extern "C" void MatterCoreStopCommandHandler()
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    if(matter_core_server_is_running())
    {
        err = matter_core_stop();
        if (err != CHIP_NO_ERROR)
            ChipLogProgress(DeviceLayer, "matter_core_stop failed!\n");

        matter_interaction_clean_up();
    }
    else
    {
        ChipLogProgress(DeviceLayer, "Matter device is already stopped!");
    }
}

/********************************************************
 * Matter Provisioning shell functions
 *********************************************************/

CHIP_ERROR MatterProvisioningCommandHelpHandler(int argc, char ** argv)
{
    sShellMatterProvisioningSubCommands.ForEachCommand(Shell::PrintCommandHelp, nullptr);
    return CHIP_NO_ERROR;
}

CHIP_ERROR MatterProvisioningCommandHandler(int argc, char ** argv)
{
    if (argc == 0)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    return sShellMatterProvisioningSubCommands.ExecCommand(argc, argv);
}

CHIP_ERROR MatterProvisioningStatusCommandHandler(int argc, char ** argv)
{
    if (argc != 0)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    if (matter_prov_is_provisioned())
    {
        ChipLogProgress(DeviceLayer, "Matter device is provisioned!");
    }
    else
    {
        ChipLogProgress(DeviceLayer, "Matter device is not provisioned!");
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR MatterProvisioningEnterProvModeCommandHandler(int argc, char ** argv)
{
    if (argc != 0)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    return matter_prov_start();
}

CHIP_ERROR MatterProvisioningExitProvModeCommandHandler(int argc, char ** argv)
{
    if (argc != 0)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    return matter_prov_stop();
}

CHIP_ERROR MatterProvisioningPrintProvTableCommandHandler(int argc, char ** argv)
{
    if (argc != 0)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    return matter_prov_print_fabric_table();
}

CHIP_ERROR MatterProvisioningEraseRowCommandHandler(int argc, char ** argv)
{
    if (argc != 1)
    {
        return MatterProvisioningCommandHelpHandler(argc, argv);
    }

    uint8_t row = atoi(argv[0]);
    return matter_prov_delete_fabric_table_row(row);
}
/**
 * @brief configures matter control shell
 *
 */
static void RegisterMatterProvisioningCommands()
{
    static const shell_command_t sMatterProvisioningSubCommands[] = {
        { &MatterProvisioningCommandHelpHandler, "help", "Usage: prov help" },
        { &MatterProvisioningStatusCommandHandler, "status", "status Usage: prov status" },
        { &MatterProvisioningEnterProvModeCommandHandler, "enterprovmode", "enterprovmode Usage: prov enterprovmode" },
        { &MatterProvisioningExitProvModeCommandHandler, "exitprovmode", "exitprovmode Usage: prov exitprovmode" },
        { &MatterProvisioningPrintProvTableCommandHandler, "printprovtable", "printprovtable Usage: prov printprovtable" },
        { &MatterProvisioningEraseRowCommandHandler, "eraserow", "eraserow Usage: prov eraserow <row_number>" },
    };

    static const shell_command_t sMatterProvisioningCommand = { &MatterProvisioningCommandHandler, "prov",
        "Matter Provisioning commands. Usage: prov <subcommand>" };

    // Register commands
    sShellMatterProvisioningSubCommands.RegisterCommands(sMatterProvisioningSubCommands,
        ArraySize(sMatterProvisioningSubCommands));

    Engine::Root().RegisterCommands(&sMatterProvisioningCommand, 1);
}
#endif // defined(CONFIG_ENABLE_CHIP_SHELL) && (CONFIG_ENABLE_CHIP_SHELL == 1)

} // namespace

/********************************************************
 * Switch functions
 *********************************************************/

CHIP_ERROR InitMatterProvisioningControl()
{
#if CONFIG_ENABLE_CHIP_SHELL
    RegisterMatterProvisioningCommands();
#endif
    return CHIP_NO_ERROR;
}
