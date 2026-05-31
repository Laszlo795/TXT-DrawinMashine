/*
 * Copyright (c) 2020 RTSoft. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @file ftslave.h
 * @brief TXT2 slave procedures
 */

#ifndef FT_FTSLAVE_H
#define FT_FTSLAVE_H

#include "ftalloc.h"

/**
 @brief Get TXT2 name
 @param [in] device TXT2 controller
 @return Device name
 */
const char* ftop_get_name(fttxt2 *device);

/**
 @brief Get TXT2 version
 @param [in] device TXT2 controller
 @return Device version
 */
int ftop_get_version(fttxt2 *device);

/**
 @brief Get TXT2 firmware version
 @param [in] device TXT2 controller
 @return Device firmware version
 */
int ftop_get_firmware(fttxt2 *device);

/**
 @brief Get TXT2 master Linux firmware version
 @param [in] device TXT2 controller
 @return Device master Linux firmware version
 */
const char* ftop_get_masterlinuxfirmware(void *device);

/**
 @brief Setup TXT2 mode
 @param [in] device TXT2 controller
 @param [in] mode master/slave mode
 @return error code
 */
int ftop_txt_mode(fttxt2 *device, int mode);

/**
 @brief Setup TXT2 name
 @param [in] device TXT2 controller
 @param [in] name TXT2 name for discovery
 @return error code
 */
int ftop_txt_name(fttxt2 *device, const char *name);

/**
 @brief Get number of slaves TXT2
 @param [in] device TXT2 controller
 @return number of slaves TXT2
 */
unsigned int ftop_get_slaves_number(fttxt2 *device);

/**
 @brief Get TXT2 slave uid
 @param [in] device TXT2 controller
 @param [in] number slave number
 @return slave uid
 */
uint32_t ftop_get_txt_uid(fttxt2 *device, unsigned int number);

/**
 @brief Get TXT2 slave name
 @param [in] device master TXT2 controller
 @param [in] number slave number
 @return slave name
 */
const char *ftop_get_txt_name(fttxt2 *device, unsigned int number);

/**
 @brief Get TXT2 master linux firmware
 @param [in] device master TXT2 controller
 @return slave name
 */
const char *ftop_get_txt_masterlinuxfirmware(void *device);

/**
 @brief Get TXT2 slave serial number
 @param [in] device master TXT2 controller
 @param [in] number slave number
 @return slave serial number
 */
const char *ftop_get_txt_SN(fttxt2 *device, unsigned int number);

/**
 @brief Get TXT2 slave
 @param [in] device TXT2 controller
 @param [in] number slave number
 @return TXT2 device
 */
void *ftop_get_slave_by_order(fttxt2 *device, unsigned int number);

/**
 @brief Get TXT2 slave
 @param [in] device master TXT2 controller
 @param [in] uid slave uid
 @return TXT2 device
 */
void *ftop_get_slave_by_uid(fttxt2 *device, unsigned int uid);

/**
 @brief Get TXT2 slave
 @param [in] device master TXT2 controller
 @param [in] name slave name
 @return TXT2 device
 */
void *ftop_get_slave_by_name(fttxt2 *device, const char *name);

/**
 @brief Get TXT2 slave
 @param [in] device master TXT2 controller
 @param [in] sn slave serial number
 @return TXT2 device
 */
void *ftop_get_slave_by_SN(fttxt2 *device, const char *sn);

#endif /* FT_FTSLAVE_H */
