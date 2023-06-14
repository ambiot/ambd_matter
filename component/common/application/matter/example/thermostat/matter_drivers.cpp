#include "matter_drivers.h"
#include "matter_interaction.h"
#include "thermostat.h"
#include "thermostat_ui.h"
#include "gpio_irq_api.h"

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>

using namespace ::chip::app;

uint32_t identifyTimerCount;
constexpr uint32_t kIdentifyTimerDelayMS     = 250;

MatterThermostatUI ui;
MatterThermostat thermostat;

// Set identify cluster and its callback on ep1
static Identify gIdentify1 = {
    chip::EndpointId{ 1 }, matter_driver_on_identify_start, matter_driver_on_identify_stop, EMBER_ZCL_IDENTIFY_IDENTIFY_TYPE_VISIBLE_LED, matter_driver_on_trigger_effect,
};

void matter_driver_on_identify_start(Identify * identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStart");
}

void matter_driver_on_identify_stop(Identify * identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStop");
}

void matter_driver_on_trigger_effect(Identify * identify)
{
    switch (identify->mCurrentEffectIdentifier)
    {
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BLINK:
        ChipLogProgress(Zcl, "EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BLINK");
        break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BREATHE:
        ChipLogProgress(Zcl, "EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_BREATHE");
        break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_OKAY:
        ChipLogProgress(Zcl, "EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_OKAY");
        break;
    case EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_CHANNEL_CHANGE:
        ChipLogProgress(Zcl, "EMBER_ZCL_IDENTIFY_EFFECT_IDENTIFIER_CHANNEL_CHANGE");
        break;
    default:
        ChipLogProgress(Zcl, "No identifier effect");
        return;
    }
}

void IdentifyTimerHandler(chip::System::Layer * systemLayer, void * appState, CHIP_ERROR error)
{
    if (identifyTimerCount)
    {
        identifyTimerCount--;
    }
}

void matter_driver_OnIdentifyPostAttributeChangeCallback(uint8_t * value)
{
    // timerCount represents the number of callback executions before we stop the timer.
    // value is expressed in seconds and the timer is fired every 250ms, so just multiply value by 4.
    // Also, we want timerCount to be odd number, so the ligth state ends in the same state it starts.
    identifyTimerCount = (*value) * 4;
exit:
    return;
}

CHIP_ERROR matter_driver_thermostat_init()
{
    thermostat.Init();
    return CHIP_NO_ERROR;
}

CHIP_ERROR matter_driver_thermostat_ui_init()
{
    ui.Init();
    return CHIP_NO_ERROR;
}

CHIP_ERROR matter_driver_thermostat_ui_set_startup_value()
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    EmberAfStatus getstatus;
    DataModel::Nullable<int16_t> temp;
    int16_t OccupiedCoolingSetpoint;
    int16_t OccupiedHeatingSetpoint;
    uint8_t SystemMode;

    chip::DeviceLayer::PlatformMgr().LockChipStack();
    getstatus = Clusters::Thermostat::Attributes::LocalTemperature::Get(1, temp);
    VerifyOrExit(getstatus == EMBER_ZCL_STATUS_SUCCESS, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::OccupiedCoolingSetpoint::Get(1, &OccupiedCoolingSetpoint);
    VerifyOrExit(getstatus == EMBER_ZCL_STATUS_SUCCESS, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::OccupiedHeatingSetpoint::Get(1, &OccupiedHeatingSetpoint);
    VerifyOrExit(getstatus == EMBER_ZCL_STATUS_SUCCESS, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::SystemMode::Get(1, &SystemMode);
    VerifyOrExit(getstatus == EMBER_ZCL_STATUS_SUCCESS, err = CHIP_ERROR_INTERNAL);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

    if (temp.IsNull())
        ui.SetLocalTemperature(0);
    else
        ui.SetLocalTemperature(temp.Value());

    ui.SetOccupiedCoolingSetpoint(OccupiedCoolingSetpoint);
    ui.SetOccupiedHeatingSetpoint(OccupiedHeatingSetpoint);
    ui.SetSystemMode(SystemMode);

    ui.UpdateDisplay();

exit:
    if (err == CHIP_ERROR_INTERNAL)
    {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }
    return err;
}

void matter_driver_uplink_update_handler(AppEvent *aEvent)
{
    chip::app::ConcreteAttributePath path = aEvent->path;

    VerifyOrExit(aEvent->path.mEndpointId == 1,
                 ChipLogError(DeviceLayer, "Unexpected EndPoint ID: `0x%02x'", path.mEndpointId));

    switch(path.mClusterId)
    {
    case Clusters::Identify::Id:
        matter_driver_OnIdentifyPostAttributeChangeCallback(&(aEvent->value._u8));
        break;
    case Clusters::Thermostat::Id:
        if(path.mAttributeId == Clusters::Thermostat::Attributes::LocalTemperature::Id)
        {
            ui.SetLocalTemperature(aEvent->value._u16);
            thermostat.Do();
        }
        if(path.mAttributeId == Clusters::Thermostat::Attributes::OccupiedCoolingSetpoint::Id)
        {
            ui.SetOccupiedCoolingSetpoint(aEvent->value._u16);
            thermostat.Do();
        }
        if(path.mAttributeId == Clusters::Thermostat::Attributes::OccupiedHeatingSetpoint::Id)
        {
            ui.SetOccupiedHeatingSetpoint(aEvent->value._u16);
            thermostat.Do();
        }
        if(path.mAttributeId == Clusters::Thermostat::Attributes::SystemMode::Id)
        {
            ui.SetSystemMode(aEvent->value._u8);
            thermostat.Do();
        }
        ui.UpdateDisplay();
        break;
    case Clusters::Scenes::Id:
        break;
    case Clusters::RelativeHumidityMeasurement::Id:
        break;
    case Clusters::FanControl::Id:
        break;
    }

exit:
    return;
}
