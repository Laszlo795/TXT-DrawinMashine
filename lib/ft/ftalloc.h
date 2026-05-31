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
  @file ftalloc.h
  @brief Allocation procedures, first argument must be TXT2
 */

#ifndef FT_FTALLOC_H
#define FT_FTALLOC_H

#include "fttypes.h"

/**
 @brief Allocate resources for local TXT
 @param [in] host host with txt controller, "auto" must be used
 @param [in] port connection port (unused)
 @return pointer to TXT2 structure
 */
fttxt2 *ftop_alloc_txt(const char *host, int port);

/**
 @brief Allocate resources for resistor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to resistor structure
 */
ftdevice *ftop_alloc_resistor(fttxt2 *txt, int num);

/**
 @brief Allocate resources for NCTTermistor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to NCTTermistor structure
 */
ftdevice *ftop_alloc_ncttermistor(fttxt2 *txt, int num);

/**
 @brief Allocate resources for switch
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to switch structure
 */
ftdevice *ftop_alloc_switch(fttxt2 *txt, int num);

/**
 @brief Allocate resources for digital
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to digital structure
 */
ftdevice *ftop_alloc_digital(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Voltmeter
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Voltmeter structure
 */
ftdevice *ftop_alloc_voltmeter(fttxt2 *txt, int num);

/**
 @brief Allocate resources for ColorSensor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to ColorSensor structure
 */
ftdevice *ftop_alloc_colorsensor(fttxt2 *txt, int num);

/**
 @brief Allocate resources for TrailFollower sensor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to TrailFollower structure
 */
ftdevice *ftop_alloc_trail_follower(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Lamp
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Lamp structure
 */
ftdevice *ftop_alloc_lamp(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Motor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Motor structure
 */
ftdevice *ftop_alloc_motor(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Encoder
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Encoder structure
 */
ftdevice *ftop_alloc_encoder(fttxt2 *txt, int num);

/**
 @brief Allocate resources for MotorStepCounter
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to MotorStepCounter structure
 */
ftdevice *ftop_alloc_motor_step_counter(fttxt2 *txt, int num);

/**
 @brief Allocate resources for MotorEncoder
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to MotorEncoder structure
 */
ftdevice *ftop_alloc_motor_encoder(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Counter
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Counter structure
 */
ftdevice *ftop_alloc_counter(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Servo motor
 @param [in] txt txt controller
 @param [in] num connection number S1-S3
 @return pointer to Servo motor structure
 */
ftdevice *ftop_alloc_servo(fttxt2 *txt, int num);

/**
 @brief Allocate resources for Ultrasonic sensor
 @param [in] txt txt controller
 @param [in] num connection number
 @return pointer to Ultrasonic structure
 */
ftdevice *ftop_alloc_ultrasonic(fttxt2 *txt, int num);

/**
 @brief Get allocation mode for connection
 @param [in] txt txt controller
 @param [in] num connection number
 @return allocation mode
 */
int ftop_alloc_mode(fttxt2 *txt, int num);

/**
 @brief Get allocation code for connection
 @param [in] txt txt controller
 @param [in] num connection number
 @return allocation code
 */
int ftop_alloc_code(fttxt2 *txt, int num);

/**
 @brief Check usage for connection
 @param [in] txt txt controller
 @param [in] num connection number
 @return usage
 */
int ftop_check_usage(fttxt2 *txt, int num);

/**
 @brief Free resources allocated for device
 @param [in] device allocated device
 @return connection number
 */
int ftop_get_conn(ftdevice *device);

/**
 @brief Get string name for a type
 @param [in] t type
 @return type name
 */
const char *ftmop_get_typename(unsigned int t);

/**
 @brief Set input extended range
 @param [in] device device
 @param [in] mode new mode: 0 - standard range, 1 - extended range
 */
void ftop_extend_range(void *device, int mode);

/**
 @brief Get TXT2 for device
 @param [in] device device connected to TXT2 controller
 @return TXT2 device
 */
void *ftop_get_txt(void *device);

/**
 @brief Free resources allocated for device
 @param [in] device allocated device
 */
void ftop_free_device(ftdevice *device);

/**
 @brief Free TXT controller, disconnect and so on
 @param [in] txt txt controller
 */
void ftop_free_txt(fttxt2 *txt);

#endif /* FT_FTALLOC_H */
