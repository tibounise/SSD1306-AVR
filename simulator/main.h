#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "../SSD1306.h"

#define SCREEN_WHITE 0
#define SCREEN_BLUE 1
#define SCREEN_BLUE_YELLOW 2

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_TYPE SCREEN_BLUE_YELLOW
#define BUFFER_SIZE 1024

struct ssd1306_register {
    // Display buffer
    uint8_t buffer[BUFFER_SIZE];

    // True => display on, false => display off
    bool status;

    // True => inverted, false => normal
    bool inverted;

    // Addressing mode
    // 0x00 => Horizontal, 0x01 => Vertical
    uint8_t addressing_mode;
};

ssd1306_register initDisplayRegister();
void fillScreen(SDL_Renderer *renderer,int color);
void drawPixel(SDL_Renderer* renderer, int x, int y);
void drawBuffer(ssd1306_register display_register,SDL_Renderer *renderer,uint8_t *buffer);
int handleExit(void *running, SDL_Event* event);