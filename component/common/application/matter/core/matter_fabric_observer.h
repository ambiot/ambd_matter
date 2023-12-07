#pragma once

#include <app/server/AppDelegate.h>
#include <app/server/Server.h>
#include <credentials/FabricTable.h>

using namespace ::chip;
using namespace ::chip::app;

class AmebaObserver : public AppDelegate, public FabricTable::Delegate
{
public:
    void OnCommissioningSessionEstablishmentStarted()
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: OnCommissioningSessionEstablishmentStarted");
    }

    void OnCommissioningSessionStarted()
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: OnCommissioningSessionStarted");
    }

    void OnCommissioningSessionEstablishmentError(CHIP_ERROR err) override
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: Commissioning error (0x%x)", err);
    }

    void OnCommissioningSessionStopped()
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: OnCommissioningSessionStopped");
    }

    void OnCommissioningWindowOpened()
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: OnCommissioningWindowOpened");
        PostEvent(chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened);
    }

    void OnCommissioningWindowClosed()
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: OnCommissioningWindowClosed");
    }

    void FabricWillBeRemoved(const FabricTable & fabricTable, chip::FabricIndex fabricIndex) override
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: Fabric 0x%x will be Removed", fabricIndex);
    }

    void OnFabricRemoved(const FabricTable & fabricTable, FabricIndex fabricIndex) override
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: Fabric 0x%x has been Removed", fabricIndex);
        if (chip::Server::GetInstance().GetFabricTable().FabricCount() == 0)
        {
            // Handle Fabric Removed here
        }
    }
    
    void OnFabricCommitted(const FabricTable & fabricTable, chip::FabricIndex fabricIndex) override
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: Fabric 0x%x has been Committed", fabricIndex);
    }

    void OnFabricUpdated(const FabricTable & fabricTable, chip::FabricIndex fabricIndex) override
    {
        ChipLogProgress(DeviceLayer, "Ameba Observer: Fabric 0x%x has been Updated", fabricIndex);
    }
};
