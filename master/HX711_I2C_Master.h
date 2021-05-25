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

#ifndef HX711_I2C_MASTER_H_026AEAA6_CF50_4631_B0A0_13490F2840E2
#define HX711_I2C_MASTER_H_026AEAA6_CF50_4631_B0A0_13490F2840E2

#include <stdint.h>
#include <Wire.h>

class HX711_I2C_Master {

protected:
    static const uint8_t _I2C_BYTES = 5;
    static constexpr int32_t _MIN_READING = -(2 ^ (24 - 1));
    static constexpr int32_t _MAX_READING = (2 ^ 24) - 1;
    const int8_t _addr;

public:

    /**
     * The HX711 is a 24-bit ADC. Values it outputs will always be
     * treated as 32-bit integers and not floating point numbers.
     */
    typedef int32_t HX_VALUE;

    enum class Format {
        MSB = 0, //most significant bit
        LSB //least significant bit
    };

    enum class Channel {
        A = 0,
        B
    };

    //Datasheet pg. 4
    enum class Gain {
        GAIN_128 = 0,
        GAIN_32 = 1,
        GAIN_64 = 2
    };

    struct HX711_Settings {
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

    };

    struct I2C_Response {
        public:

            uint16_t diff;
            int32_t reading;
        
            bool isValidReading() const noexcept {
                return this->reading >= _MIN_READING &&
                    this->reading <= _MAX_READING;
            }

            bool isMaxDiff() const noexcept {
                return this->diff = UINT16_MAX;
            }

    };

    static const int8_t DEFAULT_SLAVE_ADDR = 0x6e;

    HX711_I2C_Master(const int8_t addr = DEFAULT_SLAVE_ADDR)
        : _addr(addr) {
    }
    
    bool setSettings(const HX711_Settings s) {
        Wire.beginTransmission(this->_addr);
        Wire.write(s._cmd);
        return Wire.endTransmission() == 0;
    }

    I2C_Response getReading() const {

        I2C_Response r;
        uint8_t arr[I2C_SLAVE_BYTES]{0};
        uint8_t* ptr = arr;
        const uint8_t* end = arr + I2C_SLAVE_BYTES;

        ::Wire.requestFrom(this->_addr, I2C_SLAVE_BYTES);

        for(; ptr < end && ::Wire.available(); ++ptr) {
            *ptr = static_cast<uint8_t>(Wire.read());
        }

        if(ptr != end) {
            //something has gone wrong
        }

        r.diff = 
            (static_cast<uint16_t>(arr[0]) << 8) |
             static_cast<uint16_t>(arr[1]);

        r.reading = 
            (static_cast<int32_t>(    0)  << 24) |
            (static_cast<int32_t>(arr[2]) << 16) |
            (static_cast<int32_t>(arr[3]) <<  8) |
            (static_cast<int32_t>(arr[4]) <<  0);

        return r;

    }

};

#endif
