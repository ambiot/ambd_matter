/************************** 
* Matter OTA Related 
**************************/
#include "platform_opts.h"
#include "platform/platform_stdlib.h"

#ifdef __cplusplus
 extern "C" {
#endif

#include "stdbool.h"
#include "flash_api.h"
#include "sys_api.h"
#include "device_lock.h"
#include "chip_porting.h"

#define MATTER_OTA_SIGNATURE_SIZE 8
#define MATTER_OTA_HEADER_SIZE (32 + MATTER_OTA_SIGNATURE_SIZE)
#define MATTER_OTA_SECTOR_SIZE 4096

update_ota_target_hdr targetHeader;
bool matter_ota_first_sector_written = false;
uint32_t matter_ota_flash_sector_base;
uint32_t matter_ota_new_firmware_addr;

uint8_t matter_ota_header[MATTER_OTA_HEADER_SIZE];
uint8_t matter_ota_header_size = 0; // variable to track size of ota header
uint8_t matter_ota_buffer[MATTER_OTA_SECTOR_SIZE]; // 4KB buffer to be written to one sector
uint16_t matter_ota_buffer_size = 0; // variable to track size of buffer

uint8_t matter_ota_get_total_header_size()
{
    return MATTER_OTA_HEADER_SIZE;
}

uint8_t matter_ota_get_current_header_size()
{
    return matter_ota_header_size;
}

void matter_ota_prepare_partition()
{
    // reset header, data buffer and targetHeader
    memset(matter_ota_buffer, 0, sizeof(matter_ota_buffer));
    memset(matter_ota_header, 0, sizeof(matter_ota_header));
    memset(&targetHeader, 0, sizeof(targetHeader));
    matter_ota_header_size = 0;
    matter_ota_buffer_size = 0;

    if (ota_get_cur_index() == OTA_INDEX_1)
    {
        matter_ota_new_firmware_addr = LS_IMG2_OTA2_ADDR - SPI_FLASH_BASE;
    }
    else if (ota_get_cur_index() == OTA_INDEX_2)
    {
        matter_ota_new_firmware_addr = LS_IMG2_OTA1_ADDR - SPI_FLASH_BASE;
    }

    matter_ota_flash_sector_base = matter_ota_new_firmware_addr; // Note that the new fw address must be multiples of 4KB
}

int8_t matter_ota_store_header(uint8_t *data, uint32_t size)
{
    // check if overflow
    if (size + matter_ota_header_size > MATTER_OTA_HEADER_SIZE)
        return -1;

    memcpy(&(matter_ota_header[matter_ota_header_size]), data, size);
    matter_ota_header_size += size;

    return 1;
}

int8_t matter_ota_flash_burst_write(uint8_t *data, uint32_t size)
{
    if (size == 0)
    {
        return 1; // don't waste time, just return success
    }

    bool overflow = false;
    uint32_t sectorBase = matter_ota_flash_sector_base;
    uint32_t writeLength = MATTER_OTA_SECTOR_SIZE;
    int16_t bufferRemainSize = (int16_t) (MATTER_OTA_SECTOR_SIZE - matter_ota_buffer_size);

    if (!matter_ota_first_sector_written)
    {
        sectorBase += MATTER_OTA_SIGNATURE_SIZE; // leave first 8-bytes for signature
        writeLength -= MATTER_OTA_SIGNATURE_SIZE;
        bufferRemainSize -= MATTER_OTA_SIGNATURE_SIZE;
    }

    if (bufferRemainSize >= size)
    {
        memcpy(matter_ota_buffer + matter_ota_buffer_size, data, size);
        matter_ota_buffer_size += size;
    }
    else
    {
        memcpy(matter_ota_buffer + matter_ota_buffer_size, data, bufferRemainSize);
        matter_ota_buffer_size += bufferRemainSize;
        overflow = true;
        size -= bufferRemainSize;
    }

    if (matter_ota_buffer_size == writeLength)
    {
        // buffer is full, time to erase sector and write buffer data to flash
        erase_ota_target_flash(matter_ota_flash_sector_base + SPI_FLASH_BASE, MATTER_OTA_SECTOR_SIZE);
        ota_writestream_user(sectorBase, writeLength, matter_ota_buffer);

        if (!matter_ota_first_sector_written)
        {
            matter_ota_first_sector_written = true;
        }

        matter_ota_flash_sector_base += MATTER_OTA_SECTOR_SIZE; // point to next sector
        memset(matter_ota_buffer, 0, sizeof(matter_ota_buffer)); // clear buffer after writing
        matter_ota_buffer_size = 0;
    }

    if (overflow) // write remaining data into the newly cleared buffer
    {
        // TODO: what if it overflows twice?
        memcpy(matter_ota_buffer + matter_ota_buffer_size, data + bufferRemainSize, size);
        matter_ota_buffer_size += size;
    }

    return 1;
}

int8_t matter_ota_flush_last()
{
    // Populate the targetHeader which will be used during verify_ota_checksum()
    memcpy(&(targetHeader.FileHdr), matter_ota_header, 8);  // FwVer, HdrNum
    memcpy(&(targetHeader.FileImgHdr->ImgId), matter_ota_header + 8, 4);    // ImgId
    memcpy(&(targetHeader.FileImgHdr->ImgHdrLen), matter_ota_header + 12, 16);  // ImgHdrLen, Checksum, ImgLen, Offset
    targetHeader.FileImgHdr->FlashAddr = matter_ota_new_firmware_addr + SPI_FLASH_BASE;
    targetHeader.ValidImgCnt = 1;   // 1 image only in ota file
    memcpy(&(targetHeader.Sign), matter_ota_header + (MATTER_OTA_HEADER_SIZE - MATTER_OTA_SIGNATURE_SIZE), MATTER_OTA_SIGNATURE_SIZE);   // Signature

    if (matter_ota_buffer_size > 0)
    {
        erase_ota_target_flash(matter_ota_flash_sector_base + SPI_FLASH_BASE, MATTER_OTA_SECTOR_SIZE);
        ota_writestream_user(matter_ota_flash_sector_base, matter_ota_buffer_size, matter_ota_buffer);

        matter_ota_flash_sector_base += MATTER_OTA_SECTOR_SIZE; // point to next sector
        memset(matter_ota_buffer, 0, sizeof(matter_ota_buffer)); // clear buffer after writing
        matter_ota_buffer_size = 0;
    }

    if (strncmp("OTA", (const char *) &(targetHeader.FileImgHdr->ImgId), 3) != 0)
    {
        return -1;
    }

    if (verify_ota_checksum(&targetHeader) != 1)
    {
        return -1;
    }

    return 1;
}

int8_t matter_ota_update_signature()
{
    uint32_t targetIndex;
    if (matter_ota_new_firmware_addr = LS_IMG2_OTA2_ADDR - SPI_FLASH_BASE)
    {
        targetIndex = OTA_INDEX_2;
    }
    else
    {
        targetIndex = OTA_INDEX_1;
    }

    if (change_ota_signature(&targetHeader, targetIndex) != 1)
    {
        return -1;
    }

    return 1;
}

void matter_ota_platform_reset()
{
    ota_platform_reset();
}

static void matter_ota_abort_task(void *pvParameters)
{
    uint32_t newFWBlkSize = (MATTER_OTA_HEADER_SIZE + targetHeader.FileImgHdr->ImgLen - 1) / MATTER_OTA_SECTOR_SIZE + 1;
    printf("Cleaning up aborted OTA\r\n");
    printf("Erasing %d sectors\r\n", newFWBlkSize);

    if (matter_ota_new_firmware_addr != 0)
    {
        for (size_t i=0; i<newFWBlkSize; i++)
        {
            erase_ota_target_flash(matter_ota_new_firmware_addr + SPI_FLASH_BASE + (i * MATTER_OTA_SECTOR_SIZE), MATTER_OTA_SECTOR_SIZE);
        }
    }

    vTaskDelete(NULL);
}

void matter_ota_create_abort_task()
{
    if (xTaskCreate(matter_ota_abort_task, "matter_ota_abort", 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        printf("[%s] Failed to create matter_ota_abort_task\r\n", __FUNCTION__);
    }
}

#ifdef __cplusplus
}
#endif
