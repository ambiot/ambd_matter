#include "bridge_driver.h"
#include <support/logging/CHIPLogging.h>
#include <algorithm>
#include <platform/KeyValueStoreManager.h>
#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <platform/CHIPDeviceLayer.h>

using namespace ::chip::app;
using chip::DeviceLayer::PersistedStorage::KeyValueStoreMgr;

void MatterBridge::Init(const char * szDeviceName, const char * szLocation)
{
    memcpy(mName, szDeviceName, sizeof(mName));
    memcpy(mLocation, szLocation, sizeof(mLocation));
    ChipLogProgress(DeviceLayer, "Setting up Device[%s] at %s", mName, szLocation);

    mReachable  = false;
    mEndpointId = 0;
    mChanged_CB = nullptr;
}

void MatterBridge::SetLastStoredValue()
{
    char key[64];
    bool state;
    size_t len;
    sprintf(key, "%d/6/0", mEndpointId);
    KeyValueStoreMgr().Get(key, &state, sizeof(uint8_t), &len, 0);

    // don't trigger callback, just change the state
    mState = state;

    // update the state to matter
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    EmberAfStatus status = Clusters::OnOff::Attributes::OnOff::Set(mEndpointId, mState);

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        ChipLogError(DeviceLayer, "Updating on/off cluster failed: %x", status);
    }
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}

bool MatterBridge::IsTurnedOn()
{
    return this->mState;
}

void MatterBridge::Set(bool state, int call_callback)
{
    bool changed;

    changed = (mState != state);
    mState = state;

    ChipLogProgress(DeviceLayer, "Device[%s]: %s", mName, state ? "ON" : "OFF");

    if ((changed) && (mChanged_CB && call_callback))
    {
        mChanged_CB(this, kChanged_State);
    }

    char key[64];
    sprintf(key, "%d/6/0", mEndpointId); // endpoint_id/cluster_id/attribute_id
    KeyValueStoreMgr().Put(key, state);
}

bool MatterBridge::IsReachable()
{
    return this->mReachable;
}

void MatterBridge::SetReachable(bool aReachable)
{
    if (mReachable == aReachable)
        return;

    mReachable = aReachable;

    if (mReachable)
    {
        ChipLogProgress(DeviceLayer, "Device[%s]: ONLINE", mName);
    } 
    else
    {
        ChipLogProgress(DeviceLayer, "Device[%s]: OFFLINE", mName);
    }
}

void MatterBridge::SetName(const char * szDeviceName)
{
    bool changed = (strncmp(mName, szDeviceName, sizeof(mName)) != 0);

    ChipLogProgress(DeviceLayer, "Device[%s]: New Name=\"%s\"", mName, szDeviceName);

    memcpy(mName, szDeviceName, sizeof(mName));

    if (changed && mChanged_CB)
    {
        mChanged_CB(this, kChanged_Name);
    }
}
void MatterBridge::SetLocation(const char * szLocation)
{
    bool changed = (strncmp(mLocation, szLocation, sizeof(mLocation)) != 0);

    memcpy(mLocation, szLocation, sizeof(mLocation));

    ChipLogProgress(DeviceLayer, "Device[%s]: Location=\"%s\"", mName, mLocation);

    if (changed && mChanged_CB)
    {
        mChanged_CB(this, kChanged_Location);
    }
}

void MatterBridge::SetChangeCallback(DeviceCallback_fn aChanged_CB)
{
    mChanged_CB = aChanged_CB;
}

