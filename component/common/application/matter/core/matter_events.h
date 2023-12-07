#pragma once

#include <platform/CHIPDeviceLayer.h>
#include <app/ConcreteAttributePath.h>

struct AppEvent;
typedef void (*EventHandler)(AppEvent *);

struct AppEvent
{
    enum AppEventTypes
    {
        kEventType_Uplink = 0,
        kEventType_Downlink_OnOff,
        kEventType_Downlink_Identify,
        kEventType_Downlink_TempControl_SetPoint,
        kEventType_Downlink_Opstate_State,
        kEventType_Downlink_Opstate_Error_State,
        kEventType_Downlink_LW_SpinSpeed,
        kEventType_Downlink_LW_NumberOfRinses,
        kEventType_Downlink_LW_Mode,
        kEventType_Downlink_DW_Mode,
        kEventType_Downlink_DW_Alarm_Set,
        kEventType_Downlink_DW_Alarm_Reset,
        kEventType_Downlink_Refrigerator_Mode,
        kEventType_Downlink_Refrigerator_Alarm_State,
    };

    uint16_t Type;
    chip::app::ConcreteAttributePath path;
    union
    {
       uint8_t _u8;
       uint16_t _u16;
       uint32_t _u32;
       uint64_t _u64;
       int8_t _i8;
       int16_t _i16;
       int32_t _i32;
       int64_t _i64;
       char _str[256];
    } value;
    EventHandler mHandler;
};

namespace chip {
namespace DeviceLayer {
namespace DeviceEventType {

/**
 * Enumerates for Fabric Event
 */
enum
{
    /**
     * Indicating the Commissioning session has been established
     */
    kCommissioningSessionEstablishmentStarted = kRange_PublicPlatformSpecific + 0x1000,
    /**
     * Indicating that Commissioning session has started
     */
    kCommissioningSessionStarted,
    /**
     * Indicating the established Commissioning session encountered an error
     */
    kCommissioningSessionEstablishmentError,
    /**
     * Indicating that Commissioning session has stopped
     */
    kCommissioningSessionStopped,
    /**
     * Indicating that Commissioning window is now opened
     */
    kCommissioningWindowOpened,
    /**
     * Indicating that Commissioning window is now closed
     */
    kCommissioningWindowClosed,
    /**
     * Indicating that a fabric is about to be removed
     */
    kFabricWillBeRemoved,
    /**
     * Indicating that a fabric is removed
     */
    kFabricRemoved,
    /**
     * Indicating that a fabric in Fabric Table is persisted to storage, by CommitPendingFabricData
     */
    kFabricCommitted,
    /**
     * Indicating that operational credentials are changed, which may not be persistent
     * Can be used to affect what is needed for UpdateNOC prior to commit
    */
    kFabricUpdated,
};

} // DeviceEventType
} // DeviceLayer
} // chip
