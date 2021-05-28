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
#include "Response.h"
#include "Settings.h"
#include <Wire.h>

namespace HX711::I2C {
class Master {

protected:
    const int8_t _addr;

public:

    Master(const int8_t addr = SLAVE_ADDR)
        : _addr(addr) {
    }
    
    Response getReading() const {

        uint8_t arr[TX_BYTES]{0};
        uint8_t* ptr = arr;
        const uint8_t* end = arr + TX_BYTES;

        const uint8_t ret = ::Wire.requestFrom(
            this->_addr, TX_BYTES);

        if(ret != TX_BYTES) {
            return Response(0, 0, Response::Status::WRONG_BYTE_LEN);
        }

        for(; ptr < end && ::Wire.available(); ++ptr) {
            *ptr = static_cast<uint8_t>(::Wire.read());
        }

        //this shouldn't happen, but just to be sure...
        if(ptr != end) {
            return Response(0, 0, Response::Status::WRONG_BYTE_LEN);
        }

        return Response(arr);

    }

    bool setSettings(const Settings s) const {
        ::Wire.beginTransmission(this->_addr);
        ::Wire.write(s.getCommand());
        return ::Wire.endTransmission() == 0;
    }

};
};
#endif
