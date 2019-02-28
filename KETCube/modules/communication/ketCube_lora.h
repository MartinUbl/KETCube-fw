/**
 * @file    ketCube_lora.h
 * @author  Jan Belohoubek
 * @version 0.1
 * @date    2018-01-05
 * @brief   This file contains the KETCube module wrapper for Semtech's LoRa
 *
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 University of West Bohemia in Pilsen
 * All rights reserved.</center></h2>
 *
 * Developed by:
 * The SmartCampus Team
 * Department of Technologies and Measurement
 * www.smartcampus.cz | www.zcu.cz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), 
 * to deal with the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 *
 *    - Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *    
 *    - Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimers in the documentation 
 *      and/or other materials provided with the distribution.
 *    
 *    - Neither the names of The SmartCampus Team, Department of Technologies and Measurement
 *      and Faculty of Electrical Engineering University of West Bohemia in Pilsen, 
 *      nor the names of its contributors may be used to endorse or promote products 
 *      derived from this Software without specific prior written permission. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT HOLDERS 
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE. 
 */

 /* Define to prevent recursive inclusion ------------------------------------- */
#ifndef __KETCUBE_LORA_H
#define __KETCUBE_LORA_H

#include "ketCube_cfg.h"
#include "ketCube_common.h"

/** @defgroup KETCube_LoRa KETCube LoRa
  * @brief KETCube LoRa module
  * @ingroup KETCube_CommMods
  * @{
  */

/**
* @brief LoRa connection type
*/
typedef enum {
    KETCUBE_LORA_SELCFG_KETCube = 0,    /*<! LoRa confuguration is taken from KETCube EEPROM */
    KETCUBE_LORA_SELCFG_STATIC = 1      /*<! Static LoRa configuration as defined by SEMTECH in Comissioning.h */
} ketCube_lora_selCfg_t;

#define KETCUBE_LORA_SELCFG_SELECTED     KETCUBE_LORA_SELCFG_KETCube    /*<! Which LoRa configuration USE */

/**
* @brief LoRa devAddr type
*/
typedef enum {
    KETCUBE_LORA_SELDEVEUI_BOARD  = 0,  /*<! DevEui is automatically generated by calling BoardGetUniqueId function */
    KETCUBE_LORA_SELDEVEUI_CUSTOM = 1   /*<! LoRa user-defined devEUI is used */
} ketCube_lora_selDeveui_t;

/**
* @brief LoRa connection type
*/
typedef enum {
    KETCUBE_LORA_SELCONNMETHOD_OTAA = 0,   /*<! LoRa OTAA */
    KETCUBE_LORA_SELCONNMETHOD_ABP  = 1    /*<! LoRa ABP */
} ketCube_lora_selConnMethod_t;

/**
* @brief  Length of LoRa CFG data
*/
typedef enum {
    KETCUBE_LORA_CFGLEN_DEVEUI  =  8,   /*<! DevEUI len in bytes */
    KETCUBE_LORA_CFGLEN_APPEUI  =  8,   /*<! AppEUI len in bytes */
    KETCUBE_LORA_CFGLEN_APPKEY  = 16,   /*<! AppKEY len in bytes */
    KETCUBE_LORA_CFGLEN_NETID   =  3,   /*<! NetID len in bytes */
    KETCUBE_LORA_CFGLEN_DEVADDR =  4,   /*<! DEVAddr len in bytes */
    KETCUBE_LORA_CFGLEN_NWKSKEY = 16,   /*<! Network session KEY len in bytes */
    KETCUBE_LORA_CFGLEN_APPSKEY = 16,   /*<! Application session KEY len in bytes */
} ketCube_lora_cfgLen_t;

typedef struct ketCube_lora_cfg_t {
    ketCube_lora_selConnMethod_t connectionType; /*<! Connection type OTAA/ABP */
    ketCube_lora_selDeveui_t     devEUIType;     /*<! devEUI from device or custom devEUI */
} ketCube_lora_cfg_t;

/**
* @brief  KETCube lora module configuration
*/
typedef struct ketCube_lora_moduleCfg_t {
    ketCube_cfg_ModuleCfgByte_t coreCfg;           /*<! KETCube core cfg byte */
    
    ketCube_lora_cfg_t cfg;                        /*<! bitwise settings */
    
    byte devEUI[KETCUBE_LORA_CFGLEN_DEVEUI];       /*<! LoRaWAN devEUI */
    byte appEUI[KETCUBE_LORA_CFGLEN_APPEUI];       /*<! LoRaWAN appEUI */
    byte appKey[KETCUBE_LORA_CFGLEN_APPKEY];       /*<! LoRaWAN appKey */
    byte netID[KETCUBE_LORA_CFGLEN_NETID];         /*<! LoRaWAN network ID */
    byte devAddr[KETCUBE_LORA_CFGLEN_DEVADDR];     /*<! LoRaWAN device address */
    byte nwkSKey[KETCUBE_LORA_CFGLEN_NWKSKEY];     /*<! LoRaWAN network sesion key */
    byte appSKey[KETCUBE_LORA_CFGLEN_APPSKEY];     /*<! LoRaWAN application sesion key */
} ketCube_lora_moduleCfg_t;

extern ketCube_lora_moduleCfg_t ketCube_lora_moduleCfg;


#define KETCUBE_LORA_RX_BUFFER_LEN                          64  //< Rx buffer length

extern ketCube_cfg_ModError_t ketCube_lora_Init(ketCube_InterModMsg_t ***
                                                msg);
extern ketCube_cfg_ModError_t ketCube_lora_Send(uint8_t * buffer,
                                                uint8_t * len);
extern ketCube_cfg_ModError_t ketCube_lora_AsyncSend(uint8_t * buffer,
                                                     uint8_t * len);
extern ketCube_cfg_ModError_t ketCube_lora_SleepEnter(void);

extern void ketCube_lora_processCustomData(uint8_t * buffer, uint8_t len);

/**
* @}
*/

#endif                          /* KETCUBE_LORA_H */
