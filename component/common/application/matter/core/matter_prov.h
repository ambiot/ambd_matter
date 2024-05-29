#pragma once

#include <platform/CHIPDeviceLayer.h>

/**
 * @brief
 * This function starts provisioning mode by opening basic commissioning window
 * Even though if one fabric is already provisioned, it can still open commissioning window for different fabric provisioning
 */
CHIP_ERROR matter_prov_start(void);

/**
 * @brief
 * This function stops provisioning mode by closing commissioning window
 */
CHIP_ERROR matter_prov_stop(void);

/**
 * @brief
 * This function returns true if the matter device is provisioned by at least one admin
 */
bool matter_prov_is_provisioned(void);

/**
 * @brief
 * This function prints out the whole fabric table
 * Row starts from no 0
 */
CHIP_ERROR matter_prov_print_fabric_table(void);

/**
 * @brief
 * This function deletes fabric based on the row of the fabric table
 */
CHIP_ERROR matter_prov_delete_fabric_table_row(uint8_t row);
