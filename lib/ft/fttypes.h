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
  @file fttypes.h
  @brief Common ftop types
 */

#ifndef FT_FTTYPES_H
#define FT_FTTYPES_H

#include <stdint.h>

#define FT_MAX_SLAVES  ((FT_MAX_TXT) - 1) /*!< Only 9 TXT2 slave controllers can control master by FDCAN */
#define FT_MAX_TXT     10 /*!< Only 10 TXT2 controllers can be connected by FDCAN */
#define FT_MAX_CLIENTS  8 /*!< Only 8 parallel clients can use RPMSG */
#define FT_MAX_INPUTS   8 /*!< Only 8 inputs can be used: I1-I8 */
#define FT_MAX_OUTPUTS  8 /*!< Only 8 outputs can be used: O1-O8 */
#define FT_MAX_MOTORS   4 /*!< Only 4 motors can be used: M1-M4 */
#define FT_MAX_COUNTERS 4 /*!< Only 4 counters can be used: C1-C4 */
#define FT_MAX_SERVO    3 /*!< Only 3 servo motors can be used: S1-S3 */

#define FT_NAME_SIZE    16 /*!< TXT controller name size */

#ifdef FT_INTERNAL
typedef struct ftobject_txt2 fttxt2;	/*!< TXT controller type */
typedef struct ftobject ftdevice;		/*!< ftdevice type */
#else
typedef void fttxt2;					/*!< TXT controller type */
typedef void ftdevice;					/*!< ftdevice type */
#endif /* FTINTERNAL */

/*
 * Common types
 */
typedef uint16_t ft_pwm_type;      /*!< PWM value 0-512 */
typedef uint16_t ft_cmdid_type;    /*!< Client cmdid */
typedef uint16_t ft_counter_type;  /*!< Counter range */
typedef uint16_t ft_distance_type; /*!< Distance type */
typedef uint32_t ftuid;            /*!< TXT2 unique ID */

/**
 * Different TXT2 connections
 */
typedef enum ftobjects_connection {
    ftdev_unknown,
    ftdev_txt,           /*!< TXT2 itself */
    ftdev_i1,            /*!< I1 input */
    ftdev_i2,            /*!< I2 input */
    ftdev_i3,            /*!< I3 input */
    ftdev_i4,            /*!< I4 input */
    ftdev_i5,            /*!< I5 input */
    ftdev_i6,            /*!< I6 input */
    ftdev_i7,            /*!< I7 input */
    ftdev_i8,            /*!< I8 input */
    ftdev_o1,            /*!< O1 output */
    ftdev_m1 = ftdev_o1, /*!< M1 output */
    ftdev_o2,            /*!< O2 output */
    ftdev_o3,            /*!< O3 output */
    ftdev_m2 = ftdev_o3, /*!< M2 output */
    ftdev_o4,            /*!< O4 output */
    ftdev_o5,            /*!< O5 output */
    ftdev_m3 = ftdev_o5, /*!< M3 output */
    ftdev_o6,            /*!< O6 output */
    ftdev_o7,            /*!< O7 output */
    ftdev_m4 = ftdev_o7, /*!< M4 output */
    ftdev_o8,            /*!< O8 output */
    ftdev_c1,            /*!< C1 counter */
    ftdev_c2,            /*!< C2 counter */
    ftdev_c3,            /*!< C3 counter */
    ftdev_c4,            /*!< C4 counter */
    ftdev_s1,            /*!< S1 servo motor */
    ftdev_s2,            /*!< S2 servo motor */
    ftdev_s3,            /*!< S3 servo motor */
    ftdev_max
} ftobjects_connection;

/**
 * Different TXT2 input modes
 * digital | analog | ultrasonic - one bit must be set for real device
 */
enum ftinput_modes {
	ftinp_unknown    = 0,  /*!< unconfigured input */
	ftinp_active     = 0,  /*!< active input, for example, voltmeter */
	ftinp_passive    = 1,  /*!< passive input, for example, resistor */
	ftinp_digital    = 2,  /*!< digital input, for example, switch */
	ftinp_analog     = 4,  /*!< analog input, for example, NTC */
	ftinp_ultrasonic = 8,  /*!< ultrasonic input */
	ftinp_r1         = 0,  /*!< Range 0 - 5 V */
	ftinp_r2         = 16, /*!< Range 0 - 9 V */
};

/**
 * Different TXT2 input component types
 */
enum ftinputs_components {
    ftinput_unknown,        /*!< unconfigured input */
    ftinput_switch,         /*!< switch input */
    ftinput_voltage,        /*!< voltage input */
    ftinput_resistor,       /*!< resistor input */
    ftinput_termistor,      /*!< termistor input */
    ftinput_color_sensor,   /*!< color sensor input */
    ftinput_trail_follower, /*!< trail follower input */
    ftinput_ultrasonic,     /*!< ultrasonic input */
	ftinput_digital,        /*!< digital input */
	ftinput_encoder,        /*!< encoder */
    ftinput_max
};

/**
 * Different TXT2 communication modes
 */
enum ft_txt_mode {
    ft_txt_single, /*!< Single mode */
	ft_txt_master, /*!< Master mode */
	ft_txt_slave   /*!< Slave mode */
};

/**
 * TXT2 events
 */
enum ft_event {
    ft_event_info_update,    /*!< Common info update */
	ft_event_values_update,  /*!< Values update      */
	ft_event_slaves_update,  /*!< Slave set update   */
	ft_event_faults_update,  /*!< Faults update      */
	ft_event_max
};

/**
 * TXT2 event bits
 */
enum ft_bevent {
	ft_bevent_info_update = 1 << ft_event_info_update,
	ft_bevent_values_update = 1 << ft_event_values_update,
	ft_bevent_slaves_update = 1 << ft_event_slaves_update,
	ft_bevent_faults_update = 1 << ft_event_faults_update,
};

/**
 * TXT2 boards fault bits
 */
enum ft_faults_flags {
	FTF_OVP  = (1 << 1), /*!< overvoltage bit */
	FTF_UVLO = (1 << 2), /*!< undervoltage lock-out bit */
	FTF_OCP  = (1 << 3), /*!< overcurrent bit */
	FTF_OLD  = (1 << 4), /*!< open load bit */
	FTF_OTW  = (1 << 5), /*!< overtemperature warning bit */
	FTF_OTSD = (1 << 6), /*!< overtemperature shutdown bit */
};

/**
 * TXT2 boards faults info
 */
struct ft_faults {
	uint16_t ocp;	/*!< overcurrent bits, 2 bits per output */
	uint16_t old;   /*!< open load bits, 2 bits per output */
	uint8_t flags;  /*!< ft_faults_flags */
	uint8_t faults; /*!< bits: 1 - PWR alert, 2 - DRV8908 alert, 4 - +5V alert */
};

#endif /* FT_FTTYPES_H */
