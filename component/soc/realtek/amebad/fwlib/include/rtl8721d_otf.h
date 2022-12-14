/**
  ******************************************************************************
  * @file    rtl8721d_otf.h
  * @author
  * @version V1.0.0
  * @date    2016-05-17
  * @brief   This file contains all the functions prototypes for the flash run time decrypt firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
  ****************************************************************************** 
  */

#ifndef _RTL8721D_RSIP_H_
#define _RTL8721D_RSIP_H_

/** @addtogroup AmebaD_Platform
  * @{
  */

/** @defgroup PROTECTION 
  * @brief PROTECTION driver modules
  * @{
  */

/** @addtogroup PROTECTION
  * @verbatim
  *****************************************************************************************
  * RSIP(OTF) Introduction
  *****************************************************************************************
  *		-used for flash firmware protection, and flash firmware will be encrypted use AES.
  *		-16B KEY shoud be written to EFUSE OTP KEY area use EFUSE_OTF_KEY.
  *		-Enable should be write to EFUSE 0x19[5].
  *****************************************************************************************
  * @endverbatim
  */

/* Exported constants --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup PROTECTION_Exported_Functions OTF Exported Functions
  * @{
  */
_LONG_CALL_ void RSIP_Cmd(uint32_t NewStatus);
_LONG_CALL_ void RSIP_OTF_init(uint8_t* IV);
_LONG_CALL_ void RSIP_OTF_Cmd(uint32_t NewStatus);
_LONG_CALL_ void RSIP_OTF_Mask(uint32_t MaskIdx, uint32_t Addr, uint32_t Len, uint32_t NewStatus);
_LONG_CALL_ uint32_t RSIP_KEY_Request(uint32_t KeyTypeBit);
_LONG_CALL_ void RSIP_MMU_Config(uint32_t MMUIdx, uint32_t AddrStart, uint32_t AddrEnd, uint32_t IsMinus, uint32_t AddrOffset);
_LONG_CALL_ void RSIP_MMU_Cmd(uint32_t MMUIdx, uint32_t NewStatus);
/**
  * @}
  */

/* Registers Definitions --------------------------------------------------------*/
/**************************************************************************//**
 * @defgroup RSIP_Register_Definitions OTF Register Definitions
 * @{
 *****************************************************************************/
 
/**************************************************************************//**
 * @defgroup OTF_DEC
 * @{
 *****************************************************************************/
#define REG_SYS_OTF_DEC_CTRL				0x02D8
#define REG_SYS_OTF_DEC_ADDR_MASK0		0x02DC
#define REG_SYS_OTF_DEC_ADDR_MASK1		0x02E4
#define REG_SYS_OTF_DEC_ADDR_MASK2		0x02E8
#define REG_SYS_OTF_DEC_ADDR_MASK3		0x02EC
#define REG_SYS_OTF_DEC_IV_EXT			0x02F0
/** @} */

/**************************************************************************//**
 * @defgroup REG_OTF_DEC_CTRL
 * @{
 *****************************************************************************/
#define OTF_FEN_OTFDEC				((uint32_t)0x00000001)			/*!<function enable of OTF decoder */
#define OTF_DEC_IV_BYTE_SWAP		((uint32_t)0x00000002)			/*!<Big/little endian conversion for input OTF IV */
#define OTF_DEC_KEY_BYTE_SWAP		((uint32_t)0x00000004)			/*!<Big/little endian conversion for input OTF KEY*/
#define OTF_DEC_CIPHER_BYTE_SWAP	((uint32_t)0x00000008)			/*!Big/little endian conversion for calculated cipher*/
/** @} */

/**************************************************************************//**
 * @defgroup OTF_MASK_ENTRYx_CTRL
 * @{
 *****************************************************************************/
#define OTF_DEC_BIT_MASK_EN			((uint32_t)0x00000001)			/*!<Decoder mask enable for address~address+length */
#define OTF_DEC_BIT_MASK_SIZE			((uint32_t)0x000000FF)			/*!<Address range for decoder mask, unit is 4KB */
#define OTF_DEC_BIT_SHIFT_SIZE			8
#define IS_OTF_MASK_SIZE(SIZE) ((((SIZE) & ~OTF_DEC_BIT_MASK_SIZE) == 0x00) && (((SIZE) & OTF_DEC_BIT_MASK_SIZE) != 0x00))
/** @} */

/**************************************************************************//**
 * @defgroup MMU_ENTRYx_CTRL
 * @{
 *****************************************************************************/
#define MMU_BIT_ENTRY_VALID			((uint32_t)0x00000001)			/*!< MMU entry_x valid */
#define MMU_BIT_ENTRY_OFFSET_MINUS	((uint32_t)0x00000002)			/*!< MMU_ENTRYx_OFFSET flag, 0 Plus, 1 Minus. */
/** @} */

/**************************************************************************//**
 * @defgroup RDP_ERROR_STATUS
 * @{
 *****************************************************************************/
#define RDP_SYSTEMBIN_WRONG		((uint32_t)0x00000001)            /*!<system.bin not load to flash */
#define RDP_RDPBIN_WRONG			((uint32_t)0x00000002)            /*!<rdp.bin not load to flash */
#define RDP_KEY_REQUEST_TIMEOUT	((uint32_t)0x00000003)            /*!<Key request timeout */
#define RDP_NOT_ENABLE				((uint32_t)0x00000004)            /*!<RDP not enable in efuse */
#define RDP_CHECKSUM_ERROR		((uint32_t)0x00000005)            /*!<Check sum error */
/** @} */

/** @} */

/**
  * @}
  */

/**
  * @}
  */

/* Other definations --------------------------------------------------------*/
#define KEY_REQ_POLL_TIMES			0xFF

#endif
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
