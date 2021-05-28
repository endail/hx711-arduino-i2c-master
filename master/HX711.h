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

#ifndef HX711_H_1689EDAC_DF10_473B_90C1_8E3734299ADF
#define HX711_H_1689EDAC_DF10_473B_90C1_8E3734299ADF

#include <stdint.h>

namespace HX711 {

/**
 * The HX711 is a 24-bit ADC. Values it outputs will always be
 * treated as 32-bit integers and not floating point numbers.
 */
typedef int32_t HX_VALUE;

constexpr HX_VALUE MIN_READING = -(2 ^ ((_READ_BYTES * 8) - 1));
constexpr HX_VALUE MAX_READING = (2 ^ (_READ_BYTES * 8)) - 1;

const uint8_t BYTES_PER_CONVERSION_PERIOD = 3;

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

/**
 * Used as a map to select to correct number of clock pulses
 * depending on the set gain
 * Datasheet pg. 4
 */
const uint8_t PULSES[3] = {
    25,
    26,
    27
};

namespace I2C {
    const int8_t SLAVE_ADDR = 0x6e;
    const uint8_t TX_BYTES = 5;
};

};
#endif
