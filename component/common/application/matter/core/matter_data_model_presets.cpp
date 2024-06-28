#include <app/PluginApplicationCallbacks.h>
#include <app/util/endpoint-config-defines.h>
#include <app/util/att-storage.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/callback.h>
#include "matter_data_model.h"

using namespace chip::app::Clusters;

namespace Presets {
namespace Clusters {

// Attribute default values that are non trivial
EmberAfAttributeMinMaxValue onoffStartUpOnOffMinMaxValue = {(uint16_t)0xFF, (uint16_t)0x0, (uint16_t)0x2};
EmberAfAttributeMinMaxValue levelcontrolOptionsMinMaxValue = {(uint16_t)0x0, (uint16_t)0x0, (uint16_t)0x3};
uint8_t generalcommissioningBreadCrumbValue[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

EmberAfAttributeMetadata matter_cluster_descriptor_attributes[] = {
    {ZAP_EMPTY_DEFAULT()  , 0x0000, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0001, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0002, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0003, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0xFFFD, 2, ZAP_TYPE(INT16U)  , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)}
};

EmberAfCluster matter_cluster_descriptor_server = {
    .clusterId = 0x0000001D,
    .attributes = matter_cluster_descriptor_attributes,
    .attributeCount = ArraySize(matter_cluster_descriptor_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_acl_attributes[] = {
    {ZAP_EMPTY_DEFAULT()  , 0x0000, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0001, 0, ZAP_TYPE(ARRAY)   , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0002, 2, ZAP_TYPE(INT16U)  , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0003, 2, ZAP_TYPE(INT16U)  , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT()  , 0x0004, 2, ZAP_TYPE(INT16U)  , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U)  , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)}
};

constexpr chip::EventId matter_cluster_acl_events[] = {
    0x0000,
    0x0001,
    kInvalidEventId,
};

EmberAfCluster matter_cluster_acl_server = {
    .clusterId = 0x0000001F,
    .attributes = matter_cluster_acl_attributes,
    .attributeCount = ArraySize(matter_cluster_acl_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = matter_cluster_acl_events,
    .eventCount = ArraySize(matter_cluster_acl_events)
};

EmberAfAttributeMetadata matter_cluster_basic_information_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 2, ZAP_TYPE(VENDOR_ID), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 2, ZAP_TYPE(VENDOR_ID), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0005, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(SINGLETON) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0006, 3, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0007, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0008, 65, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0009, 4, ZAP_TYPE(INT32U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000A, 65, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000B, 17, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000C, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000D, 258, ZAP_TYPE(LONG_CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000E, 65, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x000F, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0010, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(SINGLETON) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0012, 33, ZAP_TYPE(CHAR_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
    {ZAP_EMPTY_DEFAULT(), 0x0013, 0, ZAP_TYPE(STRUCT), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(SINGLETON)},
}; // ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U) , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::EventId matter_cluster_basic_information_events[] = {
    0x0000,
    0x0001,
    0x0002,
    kInvalidEventId,
};

EmberAfCluster matter_cluster_basic_information_server = {
    .clusterId = 0x00000028,
    .attributes = matter_cluster_basic_information_attributes,
    .attributeCount = ArraySize(matter_cluster_basic_information_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = matter_cluster_basic_information_events,
    .eventCount = ArraySize(matter_cluster_basic_information_events)
};

EmberAfAttributeMetadata matter_cluster_ota_requestor_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_SIMPLE_DEFAULT(1), 0x0001, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0002, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0003, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U) , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_ota_requestor_accepted_commands[] = {
    0x0000,
    kInvalidCommandId,
};
constexpr chip::EventId matter_cluster_ota_requestor_events[] = {
    0x0000,
    0x0001,
    0x0002,
    kInvalidEventId,
};

EmberAfCluster matter_cluster_ota_requestor_server = {
    .clusterId = 0x0000002A,
    .attributes = matter_cluster_ota_requestor_attributes,
    .attributeCount = ArraySize(matter_cluster_ota_requestor_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = matter_cluster_ota_requestor_accepted_commands,
    .generatedCommandList = nullptr,
    .eventList = matter_cluster_ota_requestor_events,
    .eventCount = ArraySize(matter_cluster_ota_requestor_events)
};

EmberAfAttributeMetadata matter_cluster_general_commissioning_attributes[] = {
    {uint32_t(0), 0x0000, 8, ZAP_TYPE(INT64U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 0, ZAP_TYPE(STRUCT), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U) , ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_general_commissioning_accepted_commands[] = {
    0x0000,
    0x0002,
    0x0004,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_general_commissioning_generated_commands[] = {
    0x0001,
    0x0003,
    0x0005,
    kInvalidCommandId,
};

EmberAfCluster matter_cluster_general_commissioning_server = {
    .clusterId = 0x00000030,
    .attributes = matter_cluster_general_commissioning_attributes,
    .attributeCount = ArraySize(matter_cluster_general_commissioning_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = matter_cluster_general_commissioning_accepted_commands,
    .generatedCommandList = matter_cluster_general_commissioning_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_network_commissioning_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0005, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0006, 33, ZAP_TYPE(OCTET_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0007, 4, ZAP_TYPE(INT32S), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_network_commissioning_accepted_commands[] = {
    0x0000,
    0x0002,
    0x0004,
    0x0006,
    0x0008,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_network_commissioning_generated_commands[] = {
    0x0001,
    0x0005,
    0x0007,
    kInvalidCommandId,
};
EmberAfCluster matter_cluster_network_commissioning_server = {
    .clusterId = 0x00000031,
    .attributes = matter_cluster_network_commissioning_attributes,
    .attributeCount = ArraySize(matter_cluster_network_commissioning_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = matter_cluster_network_commissioning_accepted_commands,
    .generatedCommandList = matter_cluster_network_commissioning_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_general_diagnostics_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 8, ZAP_TYPE(INT64U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 4, ZAP_TYPE(INT32U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0005, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0006, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0007, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0008, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::EventId matter_cluster_general_diagnostics_events[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    kInvalidEventId,
};
EmberAfCluster matter_cluster_general_diagnostics_server = {
    .clusterId = 0x00000033,
    .attributes = matter_cluster_general_diagnostics_attributes,
    .attributeCount = ArraySize(matter_cluster_general_diagnostics_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = matter_cluster_general_diagnostics_events,
    .eventCount = ArraySize(matter_cluster_general_diagnostics_events)
};

EmberAfAttributeMetadata matter_cluster_software_diagnostics_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 8, ZAP_TYPE(INT64U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 8, ZAP_TYPE(INT64U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 8, ZAP_TYPE(INT64U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
EmberAfCluster matter_cluster_software_diagnostics_server = {
    .clusterId = 0x00000034,
    .attributes = matter_cluster_software_diagnostics_attributes,
    .attributeCount = ArraySize(matter_cluster_software_diagnostics_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_wifi_diagnostics_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 7, ZAP_TYPE(OCTET_STRING), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 1, ZAP_TYPE(INT8S), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(3), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::EventId matter_cluster_wifi_diagnostics_events[] = {
    0x0000,
    0x0001,
    0x0002,
    kInvalidEventId,
};
EmberAfCluster matter_cluster_wifi_diagnostics_server = {
    .clusterId = 0x00000036,
    .attributes = matter_cluster_wifi_diagnostics_attributes,
    .attributeCount = ArraySize(matter_cluster_wifi_diagnostics_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = matter_cluster_wifi_diagnostics_events,
    .eventCount = ArraySize(matter_cluster_wifi_diagnostics_events)
};

EmberAfAttributeMetadata matter_cluster_administrator_commissioning_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 1, ZAP_TYPE(FABRIC_IDX), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 1, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
EmberAfCluster matter_cluster_administrator_commissioning_server = {
    .clusterId = 0x0000003C,
    .attributes = matter_cluster_administrator_commissioning_attributes,
    .attributeCount = ArraySize(matter_cluster_administrator_commissioning_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_operational_credentials_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0005, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_operational_credentials_accepted_commands[] = {
    0x0000,
    0x0002,
    0x0004,
    0x0006,
    0x0007,
    0x000A,
    0x000B,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_operational_credentials_generated_commands[] = {
    0x0001,
    0x0003,
    0x0005,
    0x0008,
    kInvalidCommandId,
};
EmberAfCluster matter_cluster_operational_credentials_server = {
    .clusterId = 0x0000003E,
    .attributes = matter_cluster_operational_credentials_attributes,
    .attributeCount = ArraySize(matter_cluster_operational_credentials_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = matter_cluster_operational_credentials_accepted_commands,
    .generatedCommandList = matter_cluster_operational_credentials_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_group_key_management_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0001, 0, ZAP_TYPE(ARRAY), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0002, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0003, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
EmberAfCluster matter_cluster_group_key_management_server = {
    .clusterId = 0x0000003F,
    .attributes = matter_cluster_group_key_management_attributes,
    .attributeCount = ArraySize(matter_cluster_group_key_management_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = nullptr,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_identify_attributes[] = {
    {ZAP_SIMPLE_DEFAULT(0), 0x0000, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0001, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(4), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_identify_accepted_commands[] = {
    0x0000,
    0x0040,
    kInvalidCommandId,
};
EmberAfGenericClusterFunction matter_cluster_identify_functions[] = {
    (EmberAfGenericClusterFunction) emberAfIdentifyClusterServerInitCallback,
    (EmberAfGenericClusterFunction) MatterIdentifyClusterServerAttributeChangedCallback,
};
EmberAfCluster matter_cluster_identify_server = {
    .clusterId = 0x00000003,
    .attributes = matter_cluster_identify_attributes,
    .attributeCount = ArraySize(matter_cluster_identify_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(ATTRIBUTE_CHANGED_FUNCTION),
    .functions = matter_cluster_identify_functions,
    .acceptedCommandList = matter_cluster_identify_accepted_commands,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_groups_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 1, ZAP_TYPE(BITMAP8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(4), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_groups_accepted_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0005,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_groups_generated_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    kInvalidCommandId,
};
EmberAfGenericClusterFunction matter_cluster_groups_functions[] = {
    (EmberAfGenericClusterFunction) emberAfGroupsClusterServerInitCallback,
};
EmberAfCluster matter_cluster_groups_server = {
    .clusterId = 0x00000004,
    .attributes = matter_cluster_groups_attributes,
    .attributeCount = ArraySize(matter_cluster_groups_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION),
    .functions = matter_cluster_groups_functions,
    .acceptedCommandList = matter_cluster_groups_accepted_commands,
    .generatedCommandList = matter_cluster_groups_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_scenes_attributes[] = {
    {ZAP_EMPTY_DEFAULT(), 0x0000, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0001, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0002, 2, ZAP_TYPE(GROUP_ID), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x0003, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0004, 1, ZAP_TYPE(BITMAP8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {uint32_t(0), 0x0005, 8, ZAP_TYPE(NODE_ID), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0006, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_EMPTY_DEFAULT(), 0x0007, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(5), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_scenes_accepted_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0005,
    0x0006,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_scenes_generated_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0006,
    kInvalidCommandId,
};
EmberAfCluster matter_cluster_scenes_server = {
    .clusterId = 0x00000005,
    .attributes = matter_cluster_scenes_attributes,
    .attributeCount = ArraySize(matter_cluster_scenes_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER),
    .functions = NULL,
    .acceptedCommandList = matter_cluster_scenes_accepted_commands,
    .generatedCommandList = matter_cluster_scenes_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_onoff_attributes[] = {
    {ZAP_SIMPLE_DEFAULT(0), 0x0000, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE)},
    {ZAP_SIMPLE_DEFAULT(1), 0x4000, 1, ZAP_TYPE(BOOLEAN), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x4001, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_SIMPLE_DEFAULT(0), 0x4002, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {&onoffStartUpOnOffMinMaxValue, 0x4003, 1, ZAP_TYPE(ENUM8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(1), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(4), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_onoff_accepted_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0040,
    0x0041,
    0x0042,
    kInvalidCommandId,
};
constexpr chip::CommandId matter_cluster_onoff_generated_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0005,
    0x0006,
    0x0007,
    kInvalidCommandId,
};
EmberAfGenericClusterFunction matter_cluster_onoff_functions[] = {
    (EmberAfGenericClusterFunction) emberAfOnOffClusterServerInitCallback,
    (EmberAfGenericClusterFunction) MatterOnOffClusterServerShutdownCallback,
};
EmberAfCluster matter_cluster_onoff_server = {
    .clusterId = 0x00000006,
    .attributes = matter_cluster_onoff_attributes,
    .attributeCount = ArraySize(matter_cluster_onoff_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(SHUTDOWN_FUNCTION),
    .functions = matter_cluster_onoff_functions,
    .acceptedCommandList = matter_cluster_onoff_accepted_commands,
    .generatedCommandList = matter_cluster_onoff_generated_commands,
    .eventList = nullptr,
    .eventCount = 0
};

EmberAfAttributeMetadata matter_cluster_level_control_attributes[] = {
    {ZAP_SIMPLE_DEFAULT(0x01), 0x0000, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(0x0000), 0x0001, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0x01), 0x0002, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0xFE), 0x0003, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0x0000), 0x0004, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0x0000), 0x0005, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(0x0000), 0x0006, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {&levelcontrolOptionsMinMaxValue, 0x000F, 1, ZAP_TYPE(BITMAP8), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(MIN_MAX) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_SIMPLE_DEFAULT(0x0000), 0x0010, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE)},
    {ZAP_SIMPLE_DEFAULT(0xFF), 0x0011, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0012, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_EMPTY_DEFAULT(), 0x0013, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(50), 0x0014, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(255), 0x4000, 1, ZAP_TYPE(INT8U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE) | ZAP_ATTRIBUTE_MASK(TOKENIZE) | ZAP_ATTRIBUTE_MASK(WRITABLE) | ZAP_ATTRIBUTE_MASK(NULLABLE)},
    {ZAP_SIMPLE_DEFAULT(3), 0xFFFC, 4, ZAP_TYPE(BITMAP32), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
    {ZAP_SIMPLE_DEFAULT(5), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_level_control_accepted_commands[] = {
    0x0000,
    0x0001,
    0x0002,
    0x0003,
    0x0004,
    0x0005,
    0x0006,
    0x0007,
    kInvalidCommandId,
};
EmberAfGenericClusterFunction matter_cluster_level_control_functions[] = {
    (EmberAfGenericClusterFunction) emberAfLevelControlClusterServerInitCallback,
    (EmberAfGenericClusterFunction) MatterLevelControlClusterServerShutdownCallback,
};
EmberAfCluster matter_cluster_level_control_server = {
    .clusterId = 0x00000008,
    .attributes = matter_cluster_level_control_attributes,
    .attributeCount = ArraySize(matter_cluster_level_control_attributes),
    .clusterSize = 0,
    .mask = ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION) | ZAP_CLUSTER_MASK(SHUTDOWN_FUNCTION),
    .functions = matter_cluster_level_control_functions,
    .acceptedCommandList = matter_cluster_level_control_accepted_commands,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

#define MAT_ATTR_READONLY (ATTRIBUTE_MASK_EXTERNAL_STORAGE)
#define MAT_ATTR_WRITABLE (ATTRIBUTE_MASK_EXTERNAL_STORAGE | ATTRIBUTE_MASK_WRITABLE)

using namespace Thermostat::Attributes;
using namespace Thermostat::Commands;
EmberAfAttributeMetadata matter_cluster_thermostat_attributes[] = {
    {2500, LocalTemperature::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_READONLY},
    {700, AbsMinHeatSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {3000, AbsMaxHeatSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {1600, AbsMinCoolSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {3200, AbsMaxCoolSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {2000, OccupiedCoolingSetpoint::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {1600, OccupiedHeatingSetpoint::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {700, MinHeatSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {3000, MaxHeatSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {1600, MinCoolSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {3200, MaxCoolSetpointLimit::Id, 2, ZAP_TYPE(INT16S), MAT_ATTR_WRITABLE},
    {25, MinSetpointDeadBand::Id, 1, ZAP_TYPE(INT8S), MAT_ATTR_WRITABLE},
    {ZAP_EMPTY_DEFAULT(), ControlSequenceOfOperation::Id, 1, ZAP_TYPE(ENUM8), MAT_ATTR_WRITABLE},
    {ZAP_EMPTY_DEFAULT(), SystemMode::Id, 1, ZAP_TYPE(ENUM8), MAT_ATTR_WRITABLE},
    {ZAP_EMPTY_DEFAULT(), ThermostatRunningMode::Id, 1, ZAP_TYPE(ENUM8), MAT_ATTR_READONLY},
}; // ZAP_EMPTY_DEFAULT(), 0xFFFD, 2, ZAP_TYPE(INT16U), ZAP_ATTRIBUTE_MASK(EXTERNAL_STORAGE)
constexpr chip::CommandId matter_cluster_thermostat_accepted_commands[] = {
    SetpointRaiseLower::Id,
    kInvalidCommandId,
};
EmberAfCluster matter_cluster_thermostat_server = {
    .clusterId = Thermostat::Id,
    .attributes = matter_cluster_thermostat_attributes,
    .attributeCount = ArraySize(matter_cluster_thermostat_attributes),
    .clusterSize = 0,
    .mask = CLUSTER_MASK_SERVER,
    .functions = NULL,
    .acceptedCommandList = matter_cluster_thermostat_accepted_commands,
    .generatedCommandList = nullptr,
    .eventList = nullptr,
    .eventCount = 0
};

} // Clusters

namespace Endpoints {

EmberAfCluster matter_root_node_clusters[] = {
    Presets::Clusters::matter_cluster_descriptor_server,
    Presets::Clusters::matter_cluster_acl_server,
    Presets::Clusters::matter_cluster_basic_information_server,
    Presets::Clusters::matter_cluster_ota_requestor_server,
    Presets::Clusters::matter_cluster_general_commissioning_server,
    Presets::Clusters::matter_cluster_network_commissioning_server,
    Presets::Clusters::matter_cluster_general_diagnostics_server,
    Presets::Clusters::matter_cluster_software_diagnostics_server,
    Presets::Clusters::matter_cluster_wifi_diagnostics_server,
    Presets::Clusters::matter_cluster_administrator_commissioning_server,
    Presets::Clusters::matter_cluster_operational_credentials_server,
    Presets::Clusters::matter_cluster_group_key_management_server,
};
EmberAfEndpointType matter_root_node_endpoint = {
    .cluster = matter_root_node_clusters,
    .clusterCount = ArraySize(matter_root_node_clusters),
    .endpointSize = 0
};

EmberAfCluster matter_dimmable_light_clusters[] = {
    Presets::Clusters::matter_cluster_descriptor_server,
    Presets::Clusters::matter_cluster_identify_server,
    Presets::Clusters::matter_cluster_groups_server,
    Presets::Clusters::matter_cluster_scenes_server,
    Presets::Clusters::matter_cluster_onoff_server,
    Presets::Clusters::matter_cluster_level_control_server,
};
EmberAfEndpointType matter_dimmable_light_endpoint = {
    .cluster = matter_dimmable_light_clusters,
    .clusterCount = ArraySize(matter_dimmable_light_clusters),
    .endpointSize = 0
};

EmberAfCluster matter_aggregator_clusters[] = {
    Presets::Clusters::matter_cluster_descriptor_server,
};
EmberAfEndpointType matter_aggregator_endpoint = {
    .cluster = matter_aggregator_clusters,
    .clusterCount = ArraySize(matter_aggregator_clusters),
    .endpointSize = 0
};

} // Endpoints

} // Presets
