#include <stdint.h>
//#include <avr/pgmspace.h>
#include "SSD1306.h"

class Framebuffer {
public:
    Framebuffer();
    void drawBitmap(const uint8_t *bitmap, uint8_t height, uint8_t width, uint8_t pos_x, uint8_t pos_y);
    void drawBuffer(const uint8_t *buffer);
    void drawPixel(uint8_t pos_x, uint8_t pos_y, uint8_t pixel_status);
    void drawPixel(uint8_t pos_x, uint8_t pos_y);
    void drawVLine(uint8_t x, uint8_t y, uint8_t length);
    void drawHLine(uint8_t pos_y, uint8_t start, uint8_t length);
    void drawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
    void invert(uint8_t status);
    void clear();
    void show();
private:
    uint8_t buffer[1024];
    SSD1306 oled;
};