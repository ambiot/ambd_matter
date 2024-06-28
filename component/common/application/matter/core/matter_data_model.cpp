#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <app/util/attribute-storage.h>
#include "matter_data_model.h"
#include <platform/Ameba/AmebaUtils.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace ::chip;
using chip::DeviceLayer::PersistedStorage::KeyValueStoreMgr;
using namespace chip::DeviceLayer::Internal;
using chip::Protocols::InteractionModel::Status;

/* emberAfExternalAttributeRead/WriteCallback are required for externally stored attributes */
Status emberAfExternalAttributeReadCallback(EndpointId endpoint_id, ClusterId cluster_id,
                                                   const EmberAfAttributeMetadata *matter_attribute, uint8_t *buffer,
                                                   uint16_t max_read_length)
{
    Node & node = Node::getInstance();
    Endpoint *endpoint = node.getEndpoint(endpoint_id);
    const EmberAfCluster *cluster = endpoint->getCluster(cluster_id);
    const EmberAfAttributeMetadata *attribute = endpoint->getAttributeOfCluster(cluster, matter_attribute->attributeId);

    if (attribute->size > max_read_length)
    {
        ChipLogError(DeviceLayer, "[%s] Insufficient space to read Attribute 0x%08x from Cluster 0x%08x in Endpoint 0x%04x", __FUNCTION__, matter_attribute->attributeId, cluster_id, endpoint_id);
        return Status::ResourceExhausted;
    }

    Attribute attributeHelper(cluster_id, endpoint_id, attribute);
    attributeHelper.getValue(buffer);

    return Status::Success;
}

Status emberAfExternalAttributeWriteCallback(EndpointId endpoint_id, ClusterId cluster_id, const EmberAfAttributeMetadata *matter_attribute, uint8_t *buffer)
{
    Node & node = Node::getInstance();
    Endpoint *endpoint = node.getEndpoint(endpoint_id);
    const EmberAfCluster *cluster = endpoint->getCluster(cluster_id);
    const EmberAfAttributeMetadata *attribute = endpoint->getAttributeOfCluster(cluster, matter_attribute->attributeId);

    Attribute attributeHelper(cluster_id, endpoint_id, attribute);
    attributeHelper.setValue(buffer);

    return Status::Success;
}

/*                  Attributes                  */
chip::AttributeId Attribute::getAttributeId() const
{
    return attributeId;
}

chip::ClusterId Attribute::getParentClusterId() const
{
    return parentClusterId;
}

chip::ClusterId Attribute::getParentEndpointId() const
{
    return parentEndpointId;
}

std::uint16_t Attribute::getAttributeSize() const
{
    return attributeSize;
}

std::uint8_t Attribute::getAttributeType() const
{
    return attributeType;
}

std::uint8_t Attribute::getAttributeMask() const
{
    return attributeMask;
}

EmberAfDefaultOrMinMaxAttributeValue Attribute::getAttributeDefaultValue() const
{
    return defaultValue;
}

EmberAfAttributeType Attribute::getAttributeBaseType() const
{
    switch (attributeType)
    {
    case ZCL_ACTION_ID_ATTRIBUTE_TYPE:  // Action Id
    case ZCL_FABRIC_IDX_ATTRIBUTE_TYPE: // Fabric Index
    case ZCL_BITMAP8_ATTRIBUTE_TYPE:    // 8-bit bitmap
    case ZCL_ENUM8_ATTRIBUTE_TYPE:      // 8-bit enumeration
    case ZCL_STATUS_ATTRIBUTE_TYPE:     // Status Code
    case ZCL_PERCENT_ATTRIBUTE_TYPE:    // Percentage
        static_assert(std::is_same<chip::Percent, uint8_t>::value,
                      "chip::Percent is expected to be uint8_t, change this when necessary");
        return ZCL_INT8U_ATTRIBUTE_TYPE;

    case ZCL_ENDPOINT_NO_ATTRIBUTE_TYPE:   // Endpoint Number
    case ZCL_GROUP_ID_ATTRIBUTE_TYPE:      // Group Id
    case ZCL_VENDOR_ID_ATTRIBUTE_TYPE:     // Vendor Id
    case ZCL_ENUM16_ATTRIBUTE_TYPE:        // 16-bit enumeration
    case ZCL_BITMAP16_ATTRIBUTE_TYPE:      // 16-bit bitmap
    case ZCL_PERCENT100THS_ATTRIBUTE_TYPE: // 100ths of a percent
        static_assert(std::is_same<chip::EndpointId, uint16_t>::value,
                      "chip::EndpointId is expected to be uint16_t, change this when necessary");
        static_assert(std::is_same<chip::GroupId, uint16_t>::value,
                      "chip::GroupId is expected to be uint16_t, change this when necessary");
        static_assert(std::is_same<chip::Percent100ths, uint16_t>::value,
                      "chip::Percent100ths is expected to be uint16_t, change this when necessary");
        return ZCL_INT16U_ATTRIBUTE_TYPE;

    case ZCL_CLUSTER_ID_ATTRIBUTE_TYPE: // Cluster Id
    case ZCL_ATTRIB_ID_ATTRIBUTE_TYPE:  // Attribute Id
    case ZCL_FIELD_ID_ATTRIBUTE_TYPE:   // Field Id
    case ZCL_EVENT_ID_ATTRIBUTE_TYPE:   // Event Id
    case ZCL_COMMAND_ID_ATTRIBUTE_TYPE: // Command Id
    case ZCL_TRANS_ID_ATTRIBUTE_TYPE:   // Transaction Id
    case ZCL_DEVTYPE_ID_ATTRIBUTE_TYPE: // Device Type Id
    case ZCL_DATA_VER_ATTRIBUTE_TYPE:   // Data Version
    case ZCL_BITMAP32_ATTRIBUTE_TYPE:   // 32-bit bitmap
    case ZCL_EPOCH_S_ATTRIBUTE_TYPE:    // Epoch Seconds
    case ZCL_ELAPSED_S_ATTRIBUTE_TYPE:  // Elapsed Seconds
        static_assert(std::is_same<chip::ClusterId, uint32_t>::value,
                      "chip::Cluster is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::AttributeId, uint32_t>::value,
                      "chip::AttributeId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::AttributeId, uint32_t>::value,
                      "chip::AttributeId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::EventId, uint32_t>::value,
                      "chip::EventId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::CommandId, uint32_t>::value,
                      "chip::CommandId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::TransactionId, uint32_t>::value,
                      "chip::TransactionId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::DeviceTypeId, uint32_t>::value,
                      "chip::DeviceTypeId is expected to be uint32_t, change this when necessary");
        static_assert(std::is_same<chip::DataVersion, uint32_t>::value,
                      "chip::DataVersion is expected to be uint32_t, change this when necessary");
        return ZCL_INT32U_ATTRIBUTE_TYPE;

    case ZCL_EVENT_NO_ATTRIBUTE_TYPE:   // Event Number
    case ZCL_FABRIC_ID_ATTRIBUTE_TYPE:  // Fabric Id
    case ZCL_NODE_ID_ATTRIBUTE_TYPE:    // Node Id
    case ZCL_BITMAP64_ATTRIBUTE_TYPE:   // 64-bit bitmap
    case ZCL_EPOCH_US_ATTRIBUTE_TYPE:   // Epoch Microseconds
    case ZCL_POSIX_MS_ATTRIBUTE_TYPE:   // POSIX Milliseconds
    case ZCL_SYSTIME_MS_ATTRIBUTE_TYPE: // System time Milliseconds
    case ZCL_SYSTIME_US_ATTRIBUTE_TYPE: // System time Microseconds
        static_assert(std::is_same<chip::EventNumber, uint64_t>::value,
                      "chip::EventNumber is expected to be uint64_t, change this when necessary");
        static_assert(std::is_same<chip::FabricId, uint64_t>::value,
                      "chip::FabricId is expected to be uint64_t, change this when necessary");
        static_assert(std::is_same<chip::NodeId, uint64_t>::value,
                      "chip::NodeId is expected to be uint64_t, change this when necessary");
        return ZCL_INT64U_ATTRIBUTE_TYPE;

    case ZCL_TEMPERATURE_ATTRIBUTE_TYPE: // Temperature
        return ZCL_INT16S_ATTRIBUTE_TYPE;

    default:
        return attributeType;
    }
}

void Attribute::getValue(uint8_t *buffer) const
{
    switch(getAttributeBaseType())
    {
    case ZCL_INT8U_ATTRIBUTE_TYPE:
    case ZCL_BOOLEAN_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<uint8_t>(value)), sizeof(uint8_t));
        break;
    case ZCL_INT16U_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<uint16_t>(value)), sizeof(uint16_t));
        break;
    case ZCL_INT32U_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<uint32_t>(value)), sizeof(uint32_t));
        break;
    case ZCL_INT64U_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<uint64_t>(value)), sizeof(uint64_t));
        break;
    case ZCL_INT8S_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<int8_t>(value)), sizeof(int8_t));
        break;
    case ZCL_INT16S_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<int16_t>(value)), sizeof(int16_t));
        break;
    case ZCL_INT32S_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<int32_t>(value)), sizeof(int32_t));
        break;
    case ZCL_INT64S_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<int64_t>(value)), sizeof(int64_t));
        break;
    case ZCL_SINGLE_ATTRIBUTE_TYPE:
        memcpy(buffer, &(std::get<float>(value)), sizeof(float));
        break;
    case ZCL_OCTET_STRING_ATTRIBUTE_TYPE:
    case ZCL_CHAR_STRING_ATTRIBUTE_TYPE:
    case ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE:
        memcpy(buffer, valueBuffer, attributeSize);
        break;
    case ZCL_ARRAY_ATTRIBUTE_TYPE:
    case ZCL_STRUCT_ATTRIBUTE_TYPE:
        // Do nothing here, these types of attributes won't be handled here
        break;
    default:
        ChipLogError(DeviceLayer, "[%s] Unknown data type for attributeId: %d from clusterId: 0x%x", __FUNCTION__, getAttributeId(), getParentClusterId());
    }
}

void Attribute::setValue(uint8_t *buffer)
{
    switch(getAttributeBaseType())
    {
    case ZCL_INT8U_ATTRIBUTE_TYPE:
    case ZCL_BOOLEAN_ATTRIBUTE_TYPE:
        uint8_t value_uint8_t;
        memcpy(&value_uint8_t, buffer, sizeof(uint8_t));
        value = value_uint8_t;
        persistValue(&value_uint8_t, sizeof(uint8_t));
        break;
    case ZCL_INT16U_ATTRIBUTE_TYPE:
        uint16_t value_uint16_t;
        memcpy(&value_uint16_t, buffer, sizeof(uint16_t));
        value = value_uint16_t;
        persistValue((uint8_t*) &value_uint16_t, sizeof(uint16_t));
        break;
    case ZCL_INT32U_ATTRIBUTE_TYPE:
        uint32_t value_uint32_t;
        memcpy(&value_uint32_t, buffer, sizeof(uint32_t));
        value = value_uint32_t;
        persistValue((uint8_t*) &value_uint32_t, sizeof(uint32_t));
        break;
    case ZCL_INT64U_ATTRIBUTE_TYPE:
        uint64_t value_uint64_t;
        memcpy(&value_uint64_t, buffer, sizeof(uint64_t));
        value = value_uint64_t;
        persistValue((uint8_t*) &value_uint64_t, sizeof(uint64_t));
        break;
    case ZCL_INT8S_ATTRIBUTE_TYPE:
        int8_t value_int8_t;
        memcpy(&value_int8_t, buffer, sizeof(int8_t));
        value = value_int8_t;
        persistValue((uint8_t*) &value_int8_t, sizeof(int8_t));
        break;
    case ZCL_INT16S_ATTRIBUTE_TYPE:
        int16_t value_int16_t;
        memcpy(&value_int16_t, buffer, sizeof(int16_t));
        value = value_int16_t;
        persistValue((uint8_t*) &value_int16_t, sizeof(int16_t));
        break;
    case ZCL_INT32S_ATTRIBUTE_TYPE:
        int32_t value_int32_t;
        memcpy(&value_int32_t, buffer, sizeof(int32_t));
        value = value_int32_t;
        persistValue((uint8_t*) &value_int32_t, sizeof(int32_t));
        break;
    case ZCL_INT64S_ATTRIBUTE_TYPE:
        int64_t value_int64_t;
        memcpy(&value_int64_t, buffer, sizeof(int64_t));
        value = value_int64_t;
        persistValue((uint8_t*) &value_int64_t, sizeof(int64_t));
        break;
    case ZCL_SINGLE_ATTRIBUTE_TYPE:
        float value_float;
        memcpy(&value_float, buffer, sizeof(float));
        value = value_float;
        persistValue((uint8_t*) &value_float, sizeof(float));
        break;
    case ZCL_OCTET_STRING_ATTRIBUTE_TYPE:
    case ZCL_CHAR_STRING_ATTRIBUTE_TYPE:
    case ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE:
        memcpy(valueBuffer, buffer, attributeSize);
        persistValue(valueBuffer, attributeSize);
        break;
    case ZCL_ARRAY_ATTRIBUTE_TYPE:
    case ZCL_STRUCT_ATTRIBUTE_TYPE:
        break;
    default:
        break;
    }
}

void Attribute::persistValue(uint8_t *buffer, size_t size)
{
    // Only store if value is set to be stored in NVS (represented by ATTRIBUTE_MASK_TOKENIZE flag)
    if (getAttributeMask() & ATTRIBUTE_MASK_TOKENIZE)
    {
        char key[64];
        sprintf(key, "g/a/%x/%x/%x", parentEndpointId, parentClusterId, attributeId); // g/a/endpoint_id/cluster_id/attribute_id
        setPref_new(key, key, buffer, size);
    }
}

CHIP_ERROR Attribute::retrieveValue(uint8_t *buffer, size_t size)
{
    int32_t error = -1;

    // Only retrieved if value is set to be stored in NVS (represented by ATTRIBUTE_MASK_TOKENIZE flag)
    if (!(getAttributeMask() & ATTRIBUTE_MASK_TOKENIZE))
    {
        return CHIP_ERROR_INTERNAL;
    }

    char key[64];
    size_t len;
    sprintf(key, "g/a/%x/%x/%x", parentEndpointId, parentClusterId, attributeId); // g/a/endpoint_id/cluster_id/attribute_id
    return AmebaUtils::MapError(getPref_bin_new(key, key, buffer, size, &len), AmebaErrorType::kDctError);
}

/*                  Endpoint                  */
chip::EndpointId Endpoint::getEndpointId() const
{
    return endpointId;
}

const EmberAfCluster *Endpoint::getCluster(chip::ClusterId clusterId)
{
    for (size_t i=0; i<endpointMetadata->clusterCount; i++)
    {
        if (endpointMetadata->cluster[i].clusterId == clusterId)
        {
            return &endpointMetadata->cluster[i];
        }
    }

    return NULL;
}

const EmberAfAttributeMetadata *Endpoint::getAttributeOfCluster(const EmberAfCluster *cluster, chip::AttributeId attributeId)
{
    for (size_t i=0; i<cluster->attributeCount; i++)
    {
        if (cluster->attributes[i].attributeId == attributeId)
        {
            return &cluster->attributes[i];
        }
    }

    return NULL;
}

chip::EndpointId Endpoint::getParentEndpointId() const
{
    return parentEndpointId;
}

void Endpoint::setParentEndpointId(chip::EndpointId newParentEndpointId)
{
    parentEndpointId = newParentEndpointId;
}

void Endpoint::addEndpointType(EmberAfEndpointType *endpointType)
{
    endpointMetadata = endpointType;
}

void Endpoint::enableEndpoint()
{
    if (enabled)
    {
        ChipLogDetail(DeviceLayer, "Endpoint 0x%x already enabled", endpointId);
        return;
    }

    dataVersion = (chip::DataVersion*) calloc(endpointMetadata->clusterCount, sizeof(chip::DataVersion));

    // Register endpoint as dynamic endpoint in matter stack
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    CHIP_ERROR status = emberAfSetDynamicEndpoint(endpointIndex, endpointId, endpointMetadata, chip::Span<chip::DataVersion>(dataVersion, endpointMetadata->clusterCount), deviceTypeList, parentEndpointId);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

    if (status == CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "Set dynamic endpoint 0x%x success", endpointId);
        enabled = true;
        return;
    }
    else
    {
        ChipLogError(DeviceLayer, "Failed to set dynamic endpoint 0x%x with status %d", endpointId, status);
    }

    // free allocated memory if error
    free(dataVersion);
}

void Endpoint::disableEndpoint()
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    int endpointIndex = emberAfGetDynamicIndexFromEndpoint(endpointId);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

    if (endpointIndex == 0xFFFF)
    {
        ChipLogError(DeviceLayer, "Could not find endpoint index");
        return;
    }

    // clear dynamic endpoint on matter stack
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    emberAfClearDynamicEndpoint(endpointIndex);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

    enabled = false;

    // free allocated memory
    free(dataVersion);

    char key[64];

    // Clear persistent data on this endpoint
    for (size_t i=0; i<endpointMetadata->clusterCount; i++)
    {
        const EmberAfCluster *cluster = &endpointMetadata->cluster[i];
        for (size_t j=0; j<cluster->attributeCount; j++)
        {
            const EmberAfAttributeMetadata *attribute = &cluster->attributes[j];
            if (attribute->mask & ATTRIBUTE_MASK_TOKENIZE)
            {
                sprintf(key, "g/a/%x/%x/%x", endpointId, cluster->clusterId, attribute->attributeId);
                deleteKey(key, key);
            }
        }
    }
    ChipLogProgress(DeviceLayer, "Successfully disabled dynamic endpoint 0x%x", endpointId);
}

/*                  Node                  */
Node& Node::getInstance()
{
    static Node instance;
    return instance;
}

Endpoint *Node::getEndpoint(chip::EndpointId endpointId)
{
    int i=0;
    for (auto & ep : endpoints)
    {
        if (ep.getEndpointId() == endpointId)
        {
            return &ep;
        }
        i++;
    }
    return NULL;
}

chip::EndpointId Node::getNextEndpointId() const
{
    return nextEndpointId;
}

chip::EndpointId Node::addEndpoint(EmberAfEndpointType *endpointType, Span<const EmberAfDeviceType> deviceTypeList)
{
    Endpoint endpoint(this, nextEndpointId, endpointCount, deviceTypeList);
    // Set parentEndpointId based on the previous endpoint's endpointId
    if (!endpoints.empty())
    {
        endpoint.setParentEndpointId(endpoints.back().getEndpointId());
    }
    endpoint.addEndpointType(endpointType);

    endpoints.push_back(endpoint);
    endpointCount++;
    nextEndpointId++;

    return endpoint.getEndpointId();
}

void Node::removeEndpoint(chip::EndpointId endpointId)
{
    auto it = std::find_if(endpoints.begin(), endpoints.end(), [&](const Endpoint& endpoint)
    {
        return endpoint.getEndpointId() == endpointId;
    });

    if (it != endpoints.end())
    {
        // Get the index of the endpoint in the vector
        int index = std::distance(endpoints.begin(), it);

        if (it->enabled)
        {
            ChipLogError(DeviceLayer, "Endpoint not yet disabled!");
            return;
        }

        // Remove the endpoint from the vector
        endpoints.erase(it);

        // Update the parentEndpointId of subsequent endpoints
        for (int i = index; i < endpoints.size(); ++i)
        {
            if (i > 0)
            {
                endpoints[i].setParentEndpointId(endpoints[i - 1].getEndpointId());
            }
            else
            {
                // If the removed endpoint was the first one, set the parentEndpointId to 0xFFFF
                endpoints[i].setParentEndpointId(0xFFFF);
            }
        }
    }
    endpointCount--;
}

void Node::enableAllEndpoints()
{
    for (Endpoint & endpoint: endpoints)
    {
        endpoint.enableEndpoint();
    }
}

void Node::disableAllEndpoints()
{
    for (Endpoint & endpoint: endpoints)
    {
        endpoint.disableEndpoint();
    }
}