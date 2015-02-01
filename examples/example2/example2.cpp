/*
    In this example, we are going to draw bitmaps.
    The code is quite straight forward.
*/

#include "example2.h"

int main(void) {
    Framebuffer fb;

    uint8_t bitmap1[8] = {
        0b00100100,
        0b00100100,
        0b00100100,
        0b00000000,
        0b10000001,
        0b01000010,
        0b00100100,
        0b00011000
    };

    uint8_t bitmap2[8] = {
        0b11111110,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00000000
    };

    uint8_t bitmap3[8] = {
        0b00000000,
        0b00010000,
        0b00000000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00000000
    };

    uint8_t bitmap4[8] = {
        0b00000000,
        0b10000000,
        0b10000000,
        0b11111100,
        0b10000010,
        0b10000010,
        0b11111100,
        0b00000000
    };

    uint8_t bitmap5[8] = {
        0b00000000,
        0b00000000,
        0b01111110,
        0b10000001,
        0b10000001,
        0b10000001,
        0b01111110,
        0b00000000
    };

    uint8_t bitmap6[8] = {
        0b00000000,
        0b00000000,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b01111100,
        0b00000000
    };

    // Drawing the smiley stored in bitmap1[]
    for (int i = 0; i < sizeof(bitmap1); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap1[i] >> p) & 0x1) {
                fb.drawPixel(p+32,i+32);
            }
        }
    }

    for (int i = 0; i < sizeof(bitmap2); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap2[i] >> p) & 0x1) {
                fb.drawPixel(p+10,i+5);
            }
        }
    }
    for (int i = 0; i < sizeof(bitmap3); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap3[i] >> p) & 0x1) {
                fb.drawPixel(p+18,i+5);
            }
        }
    }
    for (int i = 0; i < sizeof(bitmap4); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap4[i] >> p) & 0x1) {
                fb.drawPixel((7-p)+26,i+5);
            }
        }
    }
    for (int i = 0; i < sizeof(bitmap5); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap5[i] >> p) & 0x1) {
                fb.drawPixel(p+34,i+5);
            }
        }
    }
    for (int i = 0; i < sizeof(bitmap6); ++i) {
        for (int p = 0; p < 8; ++p) {
            if ((bitmap6[i] >> p) & 0x1) {
                fb.drawPixel(p+42,i+5);
            }
        }
    }
    
    fb.show();

    return 0;
}