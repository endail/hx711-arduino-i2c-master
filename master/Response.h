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

#ifndef HX711_I2C_RESPONSE_H_B927F93B_2735_4087_97DE_4EF346B2D7D8
#define HX711_I2C_RESPONSE_H_B927F93B_2735_4087_97DE_4EF346B2D7D8

#include <stdint.h>
#include "HX711.h"

namespace HX711::I2C {
struct Response {
public:

    enum class Status {
        OK =                0,
        TIMED_OUT =         1,
        WRONG_BYTE_LEN =    2,
        INVALID_READING =   4
    };

protected:
    uint16_t _diff;
    HX_VALUE _reading;
    Status _status;

public:

    Response(const uint8_t* const arr) {

        if(arr == nullptr) {
            this->_status = Status::WRONG_BYTE_LEN;
            return;
        }

        const uint16_t diff = 
            (static_cast<uint16_t>(arr[0]) << 8) |
             static_cast<uint16_t>(arr[1]);

        const int32_t reading = 
            (static_cast<int32_t>(    0)  << 24) |
            (static_cast<int32_t>(arr[2]) << 16) |
            (static_cast<int32_t>(arr[3]) <<  8) |
            (static_cast<int32_t>(arr[4]) <<  0);

        Response(diff, reading);

    }

    Response(
        const uint16_t diff,
        const HX_VALUE reading,
        const Status status = Status::OK)
        :   _diff(diff),
            _reading(reading),
            _status(status) {

                if(!this->isValidReading()) {
                    this->_status |= Status::INVALID_READING;
                }

    }

    operator bool() const {
        return this->_status == Status::OK;
    }

    uint16_t getDiff() const {
        return this->_diff;
    }

    HX_VALUE getReading() const {
        return this->_reading;
    }

    Status getStatus() const {
        return this->_status;
    }

    void setStatus(const Status s) const {
        this->_status = s;
    }

    bool isValidReading() const {
        return this->_reading >= MIN_READING &&
            this->_reading <= MAX_READING;
    }

    bool isMaxDiff() const {
        return this->_diff == UINT16_MAX;
    }

};
};
#endif
