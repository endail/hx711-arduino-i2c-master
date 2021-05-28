// MIT License
//
// Copyright (c) 2021 Daniel Robertson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef HX711_I2C_SETTINGS_H_437F67A0_A940_4563_ACB4_9C296B7AB141
#define HX711_I2C_SETTINGS_H_437F67A0_A940_4563_ACB4_9C296B7AB141

#include <stdint.h>
#include "HX711.h"

namespace HX711::I2C {
struct Settings {
protected:
	uint8_t _cmd = 0;

public:
	
	//https://stackoverflow.com/a/47990
	void setPower(const bool p) {
		const uint8_t x = static_cast<uint8_t>(p);
		this->_cmd = (this->_cmd & ~(1UL << 5)) | (x << 5);
	}

	void setByteFormat(const Format f) {
		const uint8_t x = static_cast<uint8_t>(f);
		this->_cmd = (this->_cmd & ~(1UL << 4)) | (x << 4);
	}

	void setBitFormat(const Format f) {
		const uint8_t x = static_cast<uint8_t>(f);
		this->_cmd = (this->_cmd & ~(1UL << 3)) | (x << 3);
	}

	void setChannel(const Channel c) {
		const uint8_t x = static_cast<uint8_t>(c);
		this->_cmd = (this->_cmd & ~(1UL << 2)) | (x << 2);
	}

	void setGain(const Gain g) {
		const uint8_t x = static_cast<uint8_t>(g);
		this->_cmd &= ~0b00000011;
		this->_cmd |= (x & 0b00000011);
	}

	uint8_t getCommand() const {
		return this->_cmd;
	}

};
};
#endif
