/*!
 * \file      Commissioning.h
 *
 * \brief     End device commissioning parameters
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
*/
/**
  ******************************************************************************
  * @file    commissioning.h
  * @author  MCD Application Team
  * @brief   End device commissioning parameters
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LORA_COMMISSIONING_H__
#define __LORA_COMMISSIONING_H__

#ifdef __cplusplus
 extern "C" {
#endif
/*!
 ******************************************************************************
 ********************************** WARNING ***********************************
 ******************************************************************************
  The crypto-element implementation supports both 1.0.x and 1.1.x LoRaWAN 
  versions of the specification.
  Thus it has been decided to use the 1.1.x keys and EUI name definitions.
  The below table shows the names equivalence between versions:
               +-------------------+-------------------------+
               |       1.0.x       |          1.1.x          |
               +===================+=========================+
               | LORAWAN_DEVICE_EUI| LORAWAN_DEVICE_EUI      |
               +-------------------+-------------------------+
               | LORAWAN_APP_EUI   | LORAWAN_JOIN_EUI        |
               +-------------------+-------------------------+
               | N/A               | LORAWAN_APP_KEY         |
               +-------------------+-------------------------+
               | LORAWAN_APP_KEY   | LORAWAN_NWK_KEY         |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_F_NWK_S_INT_KEY |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_S_NWK_S_INT_KEY |
               +-------------------+-------------------------+
               | LORAWAN_NWK_S_KEY | LORAWAN_NWK_S_ENC_KEY   |
               +-------------------+-------------------------+
               | LORAWAN_APP_S_KEY | LORAWAN_APP_S_KEY       |
               +-------------------+-------------------------+
 ******************************************************************************
 ******************************************************************************
 ******************************************************************************
 */

/*!
 * When set to LORA_ENABLE the application uses the Over-the-Air activation procedure
 * When set to LORA_DISABLE the application uses the Personalization activation procedure
 */
#define OVER_THE_AIR_ACTIVATION                            LORA_ENABLE

/*!
 * Indicates if the end-device is to be connected to a private or public network
 */
#define LORAWAN_PUBLIC_NETWORK                             true

/*!
 * When set to 1 DevEui is LORAWAN_DEVICE_EUI
 * When set to 0 DevEui is automatically generated by calling
 *         BoardGetUniqueId function
 */
#define STATIC_DEVICE_EUI                     1
   
/*!
 * IEEE Organizationally Unique Identifier ( OUI ) (big endian)
 * \remark This is unique to a company or organization
 */
#define IEEE_OUI                                           0x00, 0x00, 0x00

/*!
 * Mote device IEEE EUI (big endian)
 *
 * \remark see STATIC_DEVICE_EUI comments
 */
#define LORAWAN_DEVICE_EUI                                 { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
																																			
/*!
 * App/Join server IEEE EUI (big endian)
 */
#define LORAWAN_JOIN_EUI                                   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

/*!
 * Application root key
 * WARNING: NOT USED FOR 1.0.x DEVICES
 */
#define LORAWAN_APP_KEY                                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

/*!
 * Network root key
 * WARNING: FOR 1.0.x DEVICES IT IS THE \ref LORAWAN_APP_KEY
 */
#define LORAWAN_NWK_KEY                                    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }

/*!
 * Current network ID
 */
#define LORAWAN_NETWORK_ID                                 ( uint32_t )0

/*!
 * When set to 1 DevAdd is LORAWAN_DEVICE_ADDRESS
 * When set to 0 DevAdd is automatically generated using
 *         a pseudo random generator seeded with a value derived from
 *         BoardUniqueId value
 */
#define STATIC_DEVICE_ADDRESS                     1

/*!
 * Device address on the network (big endian)
 *
 * \remark see STATIC_DEVICE_ADDRESS comments
 */
#define LORAWAN_DEVICE_ADDRESS                             ( uint32_t )0x00000000

/*!
 * Forwarding Network session integrity key
 * WARNING: NWK_S_KEY FOR 1.0.x DEVICES
 */
#define LORAWAN_F_NWK_S_INT_KEY                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }

/*!
 * Serving Network session integrity key
 * WARNING: NOT USED FOR 1.0.x DEVICES. MUST BE THE SAME AS \ref LORAWAN_F_NWK_S_INT_KEY
 */
#define LORAWAN_S_NWK_S_INT_KEY                            { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }

/*!
 * Network session encryption key
 * WARNING: NOT USED FOR 1.0.x DEVICES. MUST BE THE SAME AS \ref LORAWAN_F_NWK_S_INT_KEY
 */
#define LORAWAN_NWK_S_ENC_KEY                              { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }

/*!
 * Application session key
 */
#define LORAWAN_APP_S_KEY                                  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }


#ifdef __cplusplus
}
#endif

#endif /* __LORA_COMMISSIONING_H__ */
