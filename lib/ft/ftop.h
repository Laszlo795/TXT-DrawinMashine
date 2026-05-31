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
  @file ftop.h
  @brief Device operation procedures, first argument must be allocated device value
 */

#ifndef FT_FT_OP_H
#define FT_FT_OP_H

/**
 @brief Get resistance value
 @param [in] device resistor device
 @return resistance
 */
int ftop_get_resistance(void *device);

/**
 @brief Get voltage value
 @param [in] device Voltmeter device
 @return voltage mv
 */
int ftop_get_voltage(void *device);

/**
 @brief Get temperature value
 @param [in] device NCTTermistor device
 @return temperature
 */
int ftop_get_temperature(void *device);

/**
 @brief Get state value
 @param [in] device analog, digital or counter input device
 @return state (voltage for analog, current state for digital, counted value for counter)
 */
int ftop_get_state(void *device);

/**
 @brief Get distance value
 @param [in] device ultrasonic input device
 @return distance
 */
int ftop_get_distance(void *device);

/**
 @brief Get values
 @param [in] device TXT2 device
 @param [out] values array of values (voltage, digital value or distance for ultrasonic)
 @return status
 */
int ftop_get_values(void *device, int values[FT_MAX_INPUTS + FT_MAX_COUNTERS]);

/**
 @brief Get faults info for TXT2
 @param [in] device TXT2 device
 @param [in] finfo output structure
 @return op status
 */
int ftop_get_finfo(void *device, struct ft_faults *finfo);

/**
 @brief Set lamp brightness
 @param [in] device lamp device
 @param [in] value brightness (0-512)
 */
void ftop_set_brightness(void *device, int value);

/**
 @brief Set output PWM
 @param [in] device  device
 @param [in] value PWM duty in us
 */
void ftop_set_pwm_us(void *device, int value);

/**
 @brief Set output PWM
 @param [in] device  device
 @param [in] value PWM (0-512)
 */
void ftop_set_pwm(void *device, int value);

/**
 @brief Get saved output PWM
 @param [in] device  device
 @return PWM (0-512) value
 */
unsigned int ftop_get_pwm(void *device);

/**
 @brief Set servo limits
 @param [in] device  device
 @param [in] u16Min (300-3000) min value
 @param [in] u16Max (300-3000) max value
 */
void ftop_set_servo_limits(void *device, int num, uint16_t u16Min, uint16_t u16Max);

/**
 @brief Set servo limits
 @param [in] device  TXT2 device
 */
void ftop_init_servo_limits(void *device);

/* Motor specific procedures */

/**
 @brief Set motor step counter
 @param [in] device motor device
 @param [in] counter step counter device
 */
void ftop_motor_set_step_counter(void *device, void *counter);

/**
 @brief Set motor speed for the next operation
 @param [in] device motor device
 @param [in] speed new speed in range [-512, 512]
 */
void ftop_motor_set_speed(void *device, int speed);

/**
 @brief Immediatelly change speed and start motor
 @param [in] device motor device
 @param [in] speed new speed in range [-512, 512]
 */
void ftop_motor_start_speed(void *device, int speed);

/**
 @brief Immediatelly change speed and start motor
 @param [in] device motor device
 @param [in] distance distance
 @param [in] device2 synchronized motor device (may be NULL)
 */
void ftop_motor_start_distance(void *device, int distance, void *device2);

/**
 @brief Immediatelly change speed and start motor
 @param [in] device motor device
 @param [in] distance distance, 0 - unlimited
 @param [in] mask 4 bit mask for motors
 */
void ftop_motor_start_sync_distance(void *device, int distance, int mask);

/**
 @brief Immediatelly change speed and start motor
 @param [in] device motor device
 @param [in] mask 4 bit mask for motors
 */
void ftop_motor_stop_sync(void *device, int mask);

/**
 @brief Immediatelly stop motor
 @param [in] device motor device
 */
void ftop_motor_stop(void *device);

/**
 @brief Reset device, for example, counter
 @param [in] device motor/counter device
 */
void ftop_zero(void *device);

/**
 @brief Get distance value for motor
 @param [in] device motor device
 @return distance
 */
int ftop_motor_get_distance(void *device);

/**
 @brief Get running state for the motor
 @param [in] device the motor device
 @return motor is running
 */
_Bool ftop_motor_isrunning(void *device);

/**
 @brief Set coast mode for the motors
 @param [in] device TXT2 device
 @param [in] mask for motors
 */
void ftop_motor_coast(void *device, int mask);

/* FD CAN specific operations */

/**
 @brief Set CAN speed
 @param [in] device CAN device
 @param [in] speed new speed
 */
void ftop_can_set_bitrate(void *device, int speed);

/**
 @brief Update config
 @param [in] device TXT2 controller
 */
void ftop_update_config(void *device);

/**
 @brief Wait txt2 controller event
 @param [in] device TXT2 controller
 @param [in] emask event mask (enum ft_bevent)
 @return event mask
 */
int ftop_wait_event(void *device, uint32_t emask);

/**
 @brief Set FDCAN terminator
 @param [in] device TXT2 controller
 @param [in] mode 0 - swith off terminator, 1 switch on terminator
 */
void ftop_set_terminator(void *device, int mode);

/**
 @brief Set TXT uid
 @param [in] device TXT2 controller
 @param [in] uid - new uid
 */
void ftop_set_uid(void *device, uint32_t uid);

/**
 @brief Power down all TXT2 devices
 @param [in] device TXT2 controller
 */
void ftop_power_down(void *device);

/**
 @brief Reset all TXT2 defices
 @param [in] device TXT2 controller
 */
void ftop_reset(void *device);

#endif /* FT_FT_OP_H */
