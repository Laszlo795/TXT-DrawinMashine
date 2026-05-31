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
 * @file ft.hpp
 * @brief Common ft API C++ header for user programs
 */

#ifndef FT_FT_HPP_
#define FT_FT_HPP_

namespace ft {

extern "C" {
#define _Bool bool /*!< Macro to exclude C-C++ conflict */
#include "ft.h"
#undef _Bool
}

/* FT classes */
class TXT;

/**
 * @class Device
 * @brief Class to implement Input, Output and Servo devices on TXT2
 */
class Device {
protected:
	void *adaptee; /*!< internal implementation ftdevice */

	/**
	 @brief Get internal representation for TXT2
	 @param [in] txt txt2 class instance
	 @return pointer to the TXT internal representation
	 */
	void *getAdaptee(TXT &txt);

public:
	/**
	 @brief Get TXT2 connection
	 @return TXT2 pin connection
	 */
	int getConn() {
		return ftop_get_conn(adaptee);
	}

	virtual ~Device() {
		ftop_free_device(adaptee);
	}
};

/**
 * @class InputDevice
 * @brief Class to implement Input devices on TXT2
 */
class InputDevice : public Device {
public:
	/**
	 @brief Get device state (voltage or digital value)
	 @return device state
	 */
	int getState() {return ftop_get_state(adaptee);}

	/**
	 @brief Set normal/extended range
	 @param [in] mode 0 - normal, 1 - extended range
	 */
	void extendRange(int mode) { ftop_extend_range(adaptee, mode); }
};

/**
 * @class Lamp
 * @brief Class to implement Lamp device on TXT2
 */
class Lamp: public Device {
public:
	/**
	 @brief Get new lamp instance
	 @param [in] txt txt2 class instance
	 @param [in] output 1-8 to select O1-O8 connection
	 @return lamp instance
	 */
	Lamp(TXT &txt, int output);

	/**
	 @brief Set lamp brightness
	 @param [in] brightness new brightness 0-512
	 */
	void setBrightness(unsigned int brightness) {
		ftop_set_brightness(adaptee, brightness);
	}
};

/**
 * @class MotorDevice
 * @brief Class to implement motor devices (motor or encoder) on TXT2
 */
class MotorDevice: public Device {
public:
	/**
	 @brief Set motor speed for next operations
	 @param [in] speed new speed 0-512
	 */
	void setSpeed(int speed) {
		ftop_motor_set_speed(adaptee, speed);
	}

	/**
	 @brief Set motor speed immediatelly
	 @param [in] speed new speed 0-512
	 */
	void startSpeed(int speed) {
		ftop_motor_start_speed(adaptee, speed);
	}

	/**
	 @brief Stop motor immediatelly
	 */
	void stop() {
		ftop_motor_stop(adaptee);
	}

	/**
	 @brief Get motor number 0-3
	 @return Motor number
	 */
	int getMotor() {
		return (ftop_get_conn(adaptee) - ftdev_m1) / 2;
	}

	/**
	 @brief Use motor coast
	 */
	void coast() {
		ftop_motor_coast(ftop_get_txt(adaptee), 1 << this->getMotor());
	}
};

/**
 * @class Motor
 * @brief Class to implement Motor device on TXT2
 */
class Motor : public MotorDevice {
public:
	/**
	 @brief Get new Motor instance
	 @param [in] txt txt2 class instance
	 @param [in] output 1-4 to select M1-M4 connection
	 @return Motor instance
	 */
	Motor(TXT &txt, int output);
};

/**
 * @class Encoder
 * @brief Class to implement Encoder Motor device on TXT2
 */
class Encoder : public MotorDevice {
public:
	/**
	 @brief Get new Encoder instance
	 @param [in] txt txt2 class instance
	 @param [in] output 1-4 to select M1-M4 connection
	 @return Encoder instance
	 */
	Encoder(TXT &txt, int output);

	/**
	 @brief Start motor and stop after distance
	 @param [in] distance distance
	 @param [in] e additional Encoder for synchronization
	 */
	void startDistance(int distance, Encoder *e = 0) {
		ftop_motor_start_distance(adaptee, distance, e ? e->adaptee : 0);
	}

	/**
	 @brief Start group of motors and stop after distance
	 @param [in] distance distance
	 @param [in] mask bitmask 0x0-0xf for motors in group
	 */
	void startDistance(int distance, int mask) {
		ftop_motor_start_sync_distance(adaptee, distance, mask);
	}

	/**
	 @brief Stop group of motors
	 @param [in] mask bitmask 0x0-0xf for motors in group
	 */
	void stop(int mask) { ftop_motor_stop_sync(adaptee, mask); }

	/**
	 @brief Get current distance after startDistance call
	 @return Current distance
	 */
	int getCurrentDistance() { return ftop_motor_get_distance(adaptee); }

	/**
	 @brief Check that startDistance is executed yet
	 @return Current status
	 */
	bool isRunning() { return ftop_motor_isrunning(adaptee); }
};

/**
 * @class Servo
 * @brief Class to implement Servo Motor device on TXT2
 */
class Servo : public Device {
public:
	/**
	 @brief Get new Servo instance
	 @param [in] txt txt2 class instance
	 @param [in] output 1-3 to select S1-S3 connection
	 @return Servo instance
	 */
	Servo(TXT &txt, int output);

	/**
	 @brief Set servo motor position
	 @param [in] pwm new position 0-512
	 */
	void setPwm(int pwm) { ftop_set_pwm(adaptee, pwm); }

	/**
	 @brief Set servo motor position
	 @param [in] pwm new position 0-512
	 */
	void setPwmUs(int pwm_us) { ftop_set_pwm_us(adaptee, pwm_us); }
};

/**
 * @class Resistor
 * @brief Class to implement Resistor input device on TXT2
 */
class Resistor: public InputDevice {
public:
	/**
	 @brief Get new Resistor instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Resistor instance
	 */
	Resistor(TXT &txt, int input);

	/**
	 @brief Get resistance value
	 @return Resistance value
	 */
	int getResistance() {
		return ftop_get_resistance(adaptee);
	}
};

/**
 * @class NCTTermistor
 * @brief Class to implement NCTTermistor input device on TXT2
 */
class NCTTermistor : public InputDevice {
public:
	/**
	 @brief Get new NCTTermistor instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return NCTTermistor instance
	 */
	NCTTermistor(TXT &txt, int input);

	/**
	 @brief Get temperature value
	 @return Temperature value
	 */
	int getTemperature() { return ftop_get_temperature(adaptee); }

	/**
	 @brief Get resistance value
	 @return Resistance value
	 */
	int getResistance()  { return ftop_get_resistance(adaptee); }
};

/**
 * @class Switch
 * @brief Class to implement Switch input device on TXT2
 */
class Switch : public InputDevice {
public:
	/**
	 @brief Get new Switch instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Switch instance
	 */
	Switch(TXT &txt, int input);
};

/**
 * @class Digital
 * @brief Class to implement Digital input device on TXT2
 */
class Digital : public InputDevice {
public:
	/**
	 @brief Get new Digital instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Digital instance
	 */
	Digital(TXT &txt, int input);
};

/**
 * @class Voltmeter
 * @brief Class to implement Voltmeter input device on TXT2
 */
class Voltmeter: public InputDevice {
public:
	/**
	 @brief Get new Voltmeter instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Voltmeter instance
	 */
	Voltmeter(TXT &txt, int input);

	/**
	 @brief Get voltage value
	 @return Voltage value
	 */
	int getVoltage() {
		return ftop_get_voltage(adaptee);
	}
};

/**
 * @class ColorSensor
 * @brief Class to implement ColorSensor input device on TXT2
 */
class ColorSensor : public InputDevice {
public:
	/**
	 @brief Get new ColorSensor instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return ColorSensor instance
	 */
	ColorSensor(TXT &txt, int input);
};

/**
 * @class TrailFollower
 * @brief Class to implement TrailFollower input device on TXT2
 */
class TrailFollower : public InputDevice {
public:
	/**
	 @brief Get new TrailFollower instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return TrailFollower instance
	 */
	TrailFollower(TXT &txt, int input);
};

/**
 * @class Ultrasonic
 * @brief Class to implement Ultrasonic input device on TXT2
 */
class Ultrasonic : public InputDevice {
public:
	/**
	 @brief Get new Ultrasonic instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Ultrasonic instance
	 */
	Ultrasonic(TXT &txt, int input);

	/**
	 @brief Get distance value
	 @return Distance value
	 */
	int getDistance() { return ftop_get_distance(adaptee); }
};

/**
 * @class Counter
 * @brief Class to implement Counter device (C1-C4) on TXT2
 */
class Counter : public Device {
public:
	/**
	 @brief Get new Counter instance
	 @param [in] txt txt2 class instance
	 @param [in] input 1-4 to select C1-C4 connection
	 @return Counter instance
	 */
	Counter(TXT &txt, int input);

	/**
	 @brief Get device state (motor/button)
	 @return device state, 0 - button is pressed
	 */
	int getState() {return ftop_get_state(adaptee);}

	/**
	 @brief Get distance value
	 @return Distance value
	 */
	int getDistance() { return ftop_get_distance(adaptee); }

	/**
	 @brief Reset counter to zero
	 */
	void reset() { ftop_zero(adaptee); }
};

/**
 * @class TXT
 * @brief Class to implement the TXT2 controller itself
 */
class TXT {
	friend Device;

private:
	/**
	 @brief Get internal representation for TXT2
	 @return pointer to the TXT internal representation
	 */
	void *getAdaptee() { return adaptee;}

protected:
	void *adaptee; /*!< internal representation */

public:
	/**
	 @brief Get new TXT instance
	 @param [in] host host name, must be "auto"
	 @param [in] port ignored
	 @return TXT instance
	 */
	TXT(const std::string &host = "auto", int port = 65000) {
		adaptee = ftop_alloc_txt(host.c_str(), port);
	}

	/**
	 @brief Get slave TXT instance
	 @param [in] txt txt2 class instance
	 @param [in] slave slave number
	 @return TXT instance
	 */
	TXT(TXT &txt, int slave) {
		adaptee = ftop_get_slave_by_order(txt.adaptee, slave);
	}

	/**
	 @brief Get TXT2 name
	 @return TXT2 name
	 */
	std::string getName() { return ftop_get_name(adaptee); }

	/**
	 @brief Get TXT2 verison
	 @return TXT2 verison
	 */
	int getVersion() { return ftop_get_version(adaptee); }

	/**
	 @brief Get TXT2 fimware verison
	 @return TXT2 fimware verison
	 */
	int getFirmware() {
		return ftop_get_firmware(adaptee);
	}

	/**
	 @brief Get TXT2 mode
	 @return TXT2 mode (single/master/slave)
	 */
	void setMode(int mode) { ftop_txt_mode(adaptee, mode); }

	/**
	 @brief Set TXT2 name
	 @param [in] name new name
	 */
	void setName(const std::string &name) {
		ftop_txt_name(adaptee, name.c_str());
	}

	/**
	 @brief Get number of slaves
	 @return number of slaves
	 */
	int getSlavesNumber() { return ftop_get_slaves_number(adaptee); }

	/**
	 @brief Get slave UID
	 @param [in] number slave number
	 @return Slave UID
	 */
	uint32_t getSlaveUID(int number) { return ftop_get_txt_uid(adaptee, number); }

	/**
	 @brief Get slave name
	 @param [in] number slave number
	 @return Slave name
	 */
	std::string getSlaveName(int number) { return ftop_get_txt_name(adaptee, number); }

	/**
	 @brief Get master linux firmware
	 @return Slave name
	 */
	std::string getMasterLinuxFirmware() { return ftop_get_txt_masterlinuxfirmware(adaptee); }

	/**
	 @brief Get slave serial number
	 @param [in] number slave number
	 @return Slave serial number
	 */
	std::string getSlaveSerialNumber(int number) {
		return ftop_get_txt_SN(adaptee, number);
	}

	/**
	 @brief Get new Lamp instance
	 @param [in] output 1-8 to select O1-O8 connection
	 @return Lamp instance
	 */
	Lamp* getLamp(int output) {
		return new Lamp(*this, output);
	}

	/**
	 @brief Get new Motor instance
	 @param [in] output 1-4 to select M1-M4 connection
	 @return Motor instance
	 */
	Motor* getMotor(int output) {
		return new Motor(*this, output);
	}

	/**
	 @brief Get new Encoder instance
	 @param [in] output 1-4 to select M1-M4 connection
	 @return Encoder instance
	 */
	Encoder* getEncoder(int output) {
		return new Encoder(*this, output);
	}

	/**
	 @brief Get new Servo instance
	 @param [in] output 1-3 to select S1-S4 connection
	 @return Servo instance
	 */
	Servo* getServo(int output) {
		return new Servo(*this, output);
	}

	/**
	 @brief Get new Resistor instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Resistor instance
	 */
	Resistor *getResistor(int input) {
		return new Resistor(*this, input);
	}

	/**
	 @brief Get new NCTTermistor instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return NCTTermistor instance
	 */
	NCTTermistor *getNCTTermistor(int input) {
		return new NCTTermistor(*this, input);
	}

	/**
	 @brief Get new Switch instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Switch instance
	 */
	Switch *getSwitch(int input) {
		return new Switch(*this, input);
	}

	/**
	 @brief Get new Digital instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Digital instance
	 */
	Digital *getDigital(int input) {
		return new Digital(*this, input);
	}

	/**
	 @brief Get new Voltmeter instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Voltmeter instance
	 */
	Voltmeter *getVoltmeter(int input) {
		return new Voltmeter(*this, input);
	}

	/**
	 @brief Get new ColorSensor instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return ColorSensor instance
	 */
	ColorSensor *getColorSensor(int input) {
		return new ColorSensor(*this, input);
	}

	/**
	 @brief Get new TrailFollower instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return TrailFollower instance
	 */
	TrailFollower *getTrailFollower(int input) {
		return new TrailFollower(*this, input);
	}

	/**
	 @brief Get new Ultrasonic instance
	 @param [in] input 1-8 to select I1-I8 connection
	 @return Ultrasonic instance
	 */
	Ultrasonic *getUltrasonic(int input) {
		return new Ultrasonic(*this, input);
	}

	/**
	 @brief Get new Counter instance
	 @param [in] input 1-4 to select C1-C4 connection
	 @return Counter instance
	 */
	Counter *getCounter(int input) {
		return new Counter(*this, input);
	}

	/**
	 @brief Update config after devices allocation
	 */
	void update_config() { ftop_update_config(adaptee); }

	/**
	 @brief Set TXT2 communication bitrate
	 @param [in] bitrate new bitrate
	 */
	void setBitrate(int bitrate) {
		ftop_can_set_bitrate(adaptee, bitrate);
	}

	/**
	 @brief Set TXT2 communication terminator
	 @param [in] mode new mode, 0 - terminator off, 1 - terminator on
	 */
	void setTerminator(int mode) {
		ftop_set_terminator(adaptee, mode);
	}

	/**
	 @brief Power down M4 component
	 */
	void powerDown() { ftop_power_down(adaptee); }

	/**
	 @brief Reset M4 component
	 */
	void reset() { ftop_reset(adaptee); }
	~TXT() { ftop_free_txt(adaptee); }
};

void *Device::getAdaptee(TXT &txt) { return txt.getAdaptee(); }

Lamp::Lamp(TXT &txt, int output) {
	adaptee = ftop_alloc_lamp(getAdaptee(txt), output + ftdev_o1 - 1);
}

Motor::Motor(TXT &txt, int output) {
	adaptee = ftop_alloc_motor(getAdaptee(txt), output * 2 + ftdev_m1 - 2);
}

Encoder::Encoder(TXT &txt, int output) {
	adaptee = ftop_alloc_encoder(getAdaptee(txt), output * 2 + ftdev_m1 - 2);
}

Servo::Servo(TXT &txt, int output) {
	adaptee = ftop_alloc_servo(getAdaptee(txt), output + ftdev_s1 - 1);
}

Resistor::Resistor(TXT &txt, int input) {
	adaptee = ftop_alloc_resistor(getAdaptee(txt), input + ftdev_i1 - 1);
}

NCTTermistor::NCTTermistor(TXT &txt, int input) {
	adaptee = ftop_alloc_ncttermistor(getAdaptee(txt), input + ftdev_i1 - 1);
}

Switch::Switch(TXT &txt, int input) {
	adaptee = ftop_alloc_switch(getAdaptee(txt), input + ftdev_i1 - 1);
}

Digital::Digital(TXT &txt, int input) {
	adaptee = ftop_alloc_digital(getAdaptee(txt), input + ftdev_i1 - 1);
}

Voltmeter::Voltmeter(TXT &txt, int input) {
	adaptee = ftop_alloc_voltmeter(getAdaptee(txt), input + ftdev_i1 - 1);
}

ColorSensor::ColorSensor(TXT &txt, int input) {
	adaptee = ftop_alloc_colorsensor(getAdaptee(txt), input + ftdev_i1 - 1);
}

TrailFollower::TrailFollower(TXT &txt, int input) {
	adaptee = ftop_alloc_trail_follower(getAdaptee(txt), input + ftdev_i1 - 1);
}

Ultrasonic::Ultrasonic(TXT &txt, int input) {
	adaptee = ftop_alloc_ultrasonic(getAdaptee(txt), input + ftdev_i1 - 1);
}

Counter::Counter(TXT &txt, int input) {
	adaptee = ftop_alloc_counter(getAdaptee(txt), input + ftdev_c1 - 1);
}

}

#endif /* FT_FT_HPP_ */
