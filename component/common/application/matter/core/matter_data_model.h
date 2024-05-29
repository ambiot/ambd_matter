#pragma once

#include "af-types.h"
#include "endpoint_config.h"
#include <variant>
#include <vector>
#include <app-common/zap-generated/attribute-type.h>
#include <app/util/attribute-metadata.h>
#include <app/util/af-types.h>

using namespace ::chip;

class Node;
class Endpoint;
class Attribute;

// Use variant to represent the different data types supported
typedef std::variant<uint8_t, uint8_t*, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, float> AttributeValue;

// Attribute class
class Attribute
{
public:
    Attribute(chip::ClusterId clusterId, chip::EndpointId endpointId, const EmberAfAttributeMetadata *attributeConfig) : 
        attributeId(attributeConfig->attributeId),
        attributeSize(attributeConfig->size),
        attributeType(attributeConfig->attributeType),
        attributeMask(attributeConfig->mask),
        parentClusterId(clusterId),
        parentEndpointId(endpointId),
        defaultValue(attributeConfig->defaultValue)
    {
        // Retrieve value from NVS if available, else
        // assign value to be of base type with default value from config
        switch(getAttributeBaseType())
        {
        case ZCL_INT8U_ATTRIBUTE_TYPE:
        case ZCL_BOOLEAN_ATTRIBUTE_TYPE:
            uint8_t value_uint8_t;
            if (retrieveValue(&value_uint8_t, sizeof(uint8_t)) == CHIP_NO_ERROR)
            {
                value = value_uint8_t;
            }
            else
            {
                value = uint8_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT16U_ATTRIBUTE_TYPE:
            uint16_t value_uint16_t;
            if (retrieveValue((uint8_t*) &value_uint16_t, sizeof(uint16_t)) == CHIP_NO_ERROR)
            {
                value = value_uint16_t;
            }
            else
            {
                value = uint16_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT32U_ATTRIBUTE_TYPE:
            uint32_t value_uint32_t;
            if (retrieveValue((uint8_t*) &value_uint32_t, sizeof(uint32_t)) == CHIP_NO_ERROR)
            {
                value = value_uint32_t;
            }
            else
            {
                value = uint32_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT64U_ATTRIBUTE_TYPE:
            uint64_t value_uint64_t;
            if (retrieveValue((uint8_t*) &value_uint64_t, sizeof(uint64_t)) == CHIP_NO_ERROR)
            {
                value = value_uint64_t;
            }
            else
            {
                value = uint64_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT8S_ATTRIBUTE_TYPE:
            int8_t value_int8_t;
            if (retrieveValue((uint8_t*) &value_int8_t, sizeof(int8_t)) == CHIP_NO_ERROR)
            {
                value = value_int8_t;
            }
            else
            {
                value = int8_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT16S_ATTRIBUTE_TYPE:
            int16_t value_int16_t;
            if (retrieveValue((uint8_t*) &value_int16_t, sizeof(int16_t)) == CHIP_NO_ERROR)
            {
                value = value_int16_t;
            }
            else
            {
                value = int16_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT32S_ATTRIBUTE_TYPE:
            int32_t value_int32_t;
            if (retrieveValue((uint8_t*) &value_int32_t, sizeof(int32_t)) == CHIP_NO_ERROR)
            {
                value = value_int32_t;
            }
            else
            {
                value = int32_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_INT64S_ATTRIBUTE_TYPE:
            int64_t value_int64_t;
            if (retrieveValue((uint8_t*) &value_int64_t, sizeof(int64_t)) == CHIP_NO_ERROR)
            {
                value = value_int64_t;
            }
            else
            {
                value = int64_t(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_SINGLE_ATTRIBUTE_TYPE:
            float value_float;
            if (retrieveValue((uint8_t*) &value_float, sizeof(float)) == CHIP_NO_ERROR)
            {
                value = value_float;
            }
            else
            {
                value = float(attributeConfig->defaultValue.defaultValue);
            }
            break;
        case ZCL_OCTET_STRING_ATTRIBUTE_TYPE:
        case ZCL_CHAR_STRING_ATTRIBUTE_TYPE:
        case ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE:
            if (retrieveValue(valueBuffer, attributeSize) != CHIP_NO_ERROR)
            {
                memset(valueBuffer, 0, ATTRIBUTE_LARGEST);
                if (attributeConfig->defaultValue.ptrToDefaultValue != nullptr)
                {
                    memcpy(valueBuffer, attributeConfig->defaultValue.ptrToDefaultValue, attributeSize);
                }
            }
            break;
        case ZCL_ARRAY_ATTRIBUTE_TYPE:
        case ZCL_STRUCT_ATTRIBUTE_TYPE:
            break;
        default:
            ChipLogError(DeviceLayer, "Unknown attribute type, unable to assign value for attributeId: %d", attributeId);
            break;
        }
    }

    // Copy constructor to perform a deep copy of string values
    Attribute(const Attribute & other) :
        attributeId(other.attributeId),
        attributeSize(other.attributeSize),
        attributeType(other.attributeType),
        attributeMask(other.attributeMask),
        parentClusterId(other.parentClusterId),
        parentEndpointId(other.parentEndpointId),
        defaultValue(other.defaultValue),
        value(other.value)
    {
        switch (getAttributeBaseType())
        {
        case ZCL_OCTET_STRING_ATTRIBUTE_TYPE:
        case ZCL_CHAR_STRING_ATTRIBUTE_TYPE:
        case ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE:
            if (other.valueBuffer != nullptr)
            {
                memcpy(valueBuffer, other.valueBuffer, other.attributeSize);
            }
            break;
        default:
            break;
        }
    }

    chip::AttributeId getAttributeId() const;
    chip::ClusterId getParentClusterId() const;
    chip::ClusterId getParentEndpointId() const;
    uint16_t getAttributeSize() const;
    EmberAfAttributeType getAttributeType() const;
    EmberAfAttributeMask getAttributeMask() const;
    EmberAfDefaultOrMinMaxAttributeValue getAttributeDefaultValue() const;
    EmberAfAttributeType getAttributeBaseType() const;
    void getValue(uint8_t *buffer) const;
    void setValue(uint8_t *buffer);
    void persistValue(uint8_t *buffer, size_t size);
    CHIP_ERROR retrieveValue(uint8_t *buffer, size_t size);

private:
    chip::AttributeId attributeId;
    uint16_t attributeSize;
    EmberAfAttributeType attributeType;
    EmberAfAttributeMask attributeMask;
    chip::ClusterId parentClusterId;
    chip::EndpointId parentEndpointId;
    EmberAfDefaultOrMinMaxAttributeValue defaultValue;
    AttributeValue value;
    uint8_t valueBuffer[ATTRIBUTE_LARGEST];
};

/** Command flags */
/** The command is not a standard command */
#define COMMAND_MASK_CUSTOM (0x01)
/** The command is client generated */
#define COMMAND_MASK_ACCEPTED (0x02)
/** The command is server generated */
#define COMMAND_MASK_GENERATED (0x04)

// Endpoint class
class Endpoint
{
public:
    friend class Node;

    Endpoint(Node* node, chip::EndpointId endpointId, uint16_t endpointCount, Span<const EmberAfDeviceType> deviceTypeList) :
        endpointId(endpointId),
        endpointIndex(endpointCount),
        parentEndpointId(0xFFFF /* chip::kInvalidEndpointId */),
        parentNode(node),
        deviceTypeList(deviceTypeList) {}
    chip::EndpointId getEndpointId() const;
    const EmberAfCluster *getCluster(chip::ClusterId clusterId);
    const EmberAfAttributeMetadata *getAttributeOfCluster(const EmberAfCluster *cluster, chip::AttributeId attributeId);
    chip::EndpointId getParentEndpointId() const;   // This returns the endpointId of the previous endpoint, not to be confused with Cluster::getParentEndpointId
    void setParentEndpointId(chip::EndpointId parentEndpointId);
    void addEndpointType(EmberAfEndpointType *endpointType);
    void enableEndpoint();
    void disableEndpoint();

private:
    chip::EndpointId endpointId;
    uint16_t endpointIndex;
    chip::EndpointId parentEndpointId;
    Node* parentNode;
    chip::DataVersion *dataVersion = nullptr;
    Span<const EmberAfDeviceType> deviceTypeList;
    EmberAfEndpointType *endpointMetadata;
    bool enabled = false;
};

// Node class
class Node
{
public:
    static Node& getInstance();
    Endpoint *getEndpoint(chip::EndpointId endpointId);
    chip::EndpointId getNextEndpointId() const;
    chip::EndpointId addEndpoint(EmberAfEndpointType *endpointType, Span<const EmberAfDeviceType> deviceTypeList);
    void removeEndpoint(chip::EndpointId endpointId);
    void enableAllEndpoints();
    void disableAllEndpoints();

private:
    Node() {} /* singleton instance */
    chip::EndpointId endpointCount = 0;
    chip::EndpointId nextEndpointId = 0;
    std::vector<Endpoint> endpoints;
};
