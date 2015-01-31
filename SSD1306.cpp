/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

#include <stdint.h>
#include "SSD1306.h"

#ifdef SIMULATOR
#include "simulator/I2C.h"
#else
#include "I2C.h"
#endif

SSD1306::SSD1306() {
    i2c.init(SSD1306_DEFAULT_ADDRESS);

    // Turn display off
    sendCommand(SSD1306_DISPLAYOFF);

    sendCommand(SSD1306_SETDISPLAYCLOCKDIV);
    sendCommand(0x80);

    sendCommand(SSD1306_SETMULTIPLEX);
    sendCommand(0x3F);
    
    sendCommand(SSD1306_SETDISPLAYOFFSET);
    sendCommand(0x00);
    
    sendCommand(SSD1306_SETSTARTLINE | 0x00);
    
    // We use internal charge pump
    sendCommand(SSD1306_CHARGEPUMP);
    sendCommand(0x14);
    
    // Horizontal memory mode
    sendCommand(SSD1306_MEMORYMODE);
    sendCommand(0x00);
    
    sendCommand(SSD1306_SEGREMAP | 0x1);

    sendCommand(SSD1306_COMSCANDEC);

    sendCommand(SSD1306_SETCOMPINS);
    sendCommand(0x12);

    // Max contrast
    sendCommand(SSD1306_SETCONTRAST);
    sendCommand(0xCF);

    sendCommand(SSD1306_SETPRECHARGE);
    sendCommand(0xF1);

    sendCommand(SSD1306_SETVCOMDETECT);
    sendCommand(0x40);

    sendCommand(SSD1306_DISPLAYALLON_RESUME);

    // Non-inverted display
    sendCommand(SSD1306_NORMALDISPLAY);

    // Turn display back on
    sendCommand(SSD1306_DISPLAYON);
}

void SSD1306::sendCommand(uint8_t command) {
    i2c.start();
    i2c.write(0x00);
    i2c.write(command);
    i2c.stop();
}

void SSD1306::invert(uint8_t inverted) {
    if (inverted) {
        sendCommand(SSD1306_INVERTDISPLAY);
    } else {
        sendCommand(SSD1306_NORMALDISPLAY);
    }
}

void SSD1306::sendFramebuffer(uint8_t *buffer) {
    sendCommand(SSD1306_COLUMNADDR);
    sendCommand(0x00);
    sendCommand(0x7F);

    sendCommand(SSD1306_PAGEADDR);
    sendCommand(0x00);
    sendCommand(0x07);

    // We have to send the buffer as 16 bytes packets
    // Our buffer is 1024 bytes long, 1024/16 = 64
    // We have to send 64 packets
    for (uint8_t packet = 0; packet < 64; packet++) {
        i2c.start();
        i2c.write(0x40);
        for (uint8_t packet_byte = 0; packet_byte < 16; ++packet_byte) {
            i2c.write(buffer[packet*16+packet_byte]);
        }
        i2c.stop();
    }
}