#include <stdlib.h>
#include <stdint.h>

#include "app/server/Server.h"
#include "platform/CHIPDeviceLayer.h"
#include <lib/support/CodeUtils.h>

#include <support/CHIPMem.h>
#include <support/CodeUtils.h>
#include <core/ErrorStr.h>

using namespace ::chip;
using namespace ::chip::DeviceLayer;

CHIP_ERROR matter_prov_start()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    if (Server::GetInstance().GetCommissioningWindowManager().IsCommissioningWindowOpen())
    {
        ChipLogProgress(DeviceLayer, "Matter device is already in provisioning mode!");
    }
    else
    {
        err = Server::GetInstance().GetCommissioningWindowManager().OpenBasicCommissioningWindow();
    }
    return err;
}

CHIP_ERROR matter_prov_stop()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    if (Server::GetInstance().GetCommissioningWindowManager().IsCommissioningWindowOpen())
    {
        Server::GetInstance().GetCommissioningWindowManager().CloseCommissioningWindow();
    }
    else
    {
        ChipLogProgress(DeviceLayer, "Matter device is already out of provisioning mode!");
    }
    return err;
}

bool matter_prov_is_provisioned()
{
    return (Server::GetInstance().GetFabricTable().FabricCount() == 0 ? false : true);
}

CHIP_ERROR matter_prov_print_fabric_table()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    uint8_t fabricCount = Server::GetInstance().GetFabricTable().FabricCount();
    if (fabricCount > 0)
    {
        ChipLogProgress(DeviceLayer, "Matter device is provisioned by %i admin(s)!", fabricCount);
        uint8_t iterator = 0;
        printf("|No|FabricIndex|FabricId|NodeId|%-32s|\r\n", "FabricLabel");
        for (auto fabricIterator = Server::GetInstance().GetFabricTable().begin(); 
            fabricIterator != Server::GetInstance().GetFabricTable().end(); fabricIterator++)
        {
            printf("|%-2u|%-11u|%-8u|%-6u|", iterator++, (uint8_t*)fabricIterator->GetFabricIndex(), 
                (uint64_t*)fabricIterator->GetFabricId(), (uint64_t*)fabricIterator->GetNodeId());
            if(fabricIterator->GetFabricLabel().empty())
            {
                printf("%-32s|\r\n", "N.A.");
            }
            else
            {
                printf("%-32s|\r\n", (char*) fabricIterator->GetFabricLabel().begin());
            }
        }
    } 
    else
    {
        ChipLogProgress(DeviceLayer, "Matter device is not provisioned yet!");
    }
    return err;
}

CHIP_ERROR matter_prov_delete_fabric_table_row(uint8_t row)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    uint8_t fabricCount = Server::GetInstance().GetFabricTable().FabricCount();
    ConstFabricIterator fabricIterator = Server::GetInstance().GetFabricTable().begin();

    if(fabricCount == 0)
    {
        ChipLogError(DeviceLayer, "Matter device is not provisioned yet!");
        return err;
    }
    if(row >= fabricCount)
    {
        ChipLogError(DeviceLayer, "Invalid argument, provided row (%u) must be lower than total available fabric(s) (%u)", row, fabricCount);
        err = CHIP_ERROR_INVALID_ARGUMENT;
        return err;
    }
    for(uint8_t i = 0; i < row;i++)
    {
        fabricIterator++; //iterate fabric to targeted fabric row
    }
    err = Server::GetInstance().GetFabricTable().Delete(fabricIterator->GetFabricIndex());

    return err;
}
