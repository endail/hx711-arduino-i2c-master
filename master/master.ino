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

#include <Wire.h>

#define BAUD_RATE 115200
#define I2C_SLAVE_ADDR 0x6e
#define I2C_SLAVE_BYTES 5
#define DELAY_MS 200

void setup() {
    while(!Serial);
    Serial.begin(BAUD_RATE);
    Wire.begin();
}

void loop() {

    Wire.requestFrom(I2C_SLAVE_ADDR, I2C_SLAVE_BYTES);

    uint8_t arr[I2C_SLAVE_BYTES]{0};

    for(uint8_t* ptr = arr; ptr < arr + I2C_SLAVE_BYTES; ++ptr) {
        *ptr = static_cast<uint8_t>(Wire.read());
    }

    //reconstruct the data

    //time diff
    const uint16_t timeDiff = 
        (static_cast<uint16_t>(arr[0]) << 8) |
         static_cast<uint16_t>(arr[1]);

    //hx711 reading
    const int32_t rd = 
        (static_cast<int32_t>(     0) << 24) |
        (static_cast<int32_t>(arr[2]) << 16) |
        (static_cast<int32_t>(arr[3]) << 8)  |
        (static_cast<int32_t>(arr[4]) << 0);

    Serial.print("Diff: ");
    Serial.print(timeDiff, DEC);
    Serial.print("ms ago, Reading: ");
    Serial.println(rd, DEC);

    delay(DELAY_MS);

}