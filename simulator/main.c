#include "main.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL error : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Simulator",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ssd1306_register display_register;
    display_register = initDisplayRegister();

    uint8_t buffer_segment = 0;
    uint8_t current_byte;

    bool running = true;
    bool rerender = true;

    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
                printf("LOG : Closing simulator\n");
            }
        }

        current_byte = getchar();

        switch (current_byte) {
            case 0x00: // Command
                current_byte = getchar();
                
                switch (current_byte) {
                    case SSD1306_DISPLAYOFF:
                        printf("LOG : Turning display off\n");
                        display_register.status = false;
                        rerender = true;
                        break;
                    case SSD1306_DISPLAYON:
                        printf("LOG : Turning display on\n");
                        display_register.status = true;
                        rerender = true;
                        break;
                    case SSD1306_NORMALDISPLAY:
                        printf("LOG : Non-inverted colors\n");
                        display_register.inverted = false;
                        rerender = true;
                        break;
                    case SSD1306_INVERTDISPLAY:
                        printf("LOG : Inverted colors\n");
                        display_register.inverted = true;
                        rerender = true;
                        break;
                    case SSD1306_NOP:
                        printf("LOG : NOP command received\n");
                        break;
                    default:
                        printf("LOG : Received unknown command : 0x%x\n",current_byte);
                        break;
                }

                break;
            case 0x40: // Buffer incomming !
                printf("LOG : Receiving buffer segment %d/%d\n",buffer_segment+1,BUFFER_SIZE/16);
                for (int i = 0; i < 16; ++i) {
                    current_byte = getchar();
                    display_register.buffer[buffer_segment*16+i] = current_byte;
                }

                buffer_segment++;
                break;
        }

        if (buffer_segment == (BUFFER_SIZE/16)) {
            buffer_segment = 0;
            rerender = true;
        }

        if (rerender) {
            rerender = false;

            fillScreen(renderer,0);

            if (display_register.status) {
                drawBuffer(display_register,renderer,display_register.buffer);
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

ssd1306_register initDisplayRegister() {
    ssd1306_register display_register;

    // Filling the buffer with zeroes
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        display_register.buffer[i] = 0x00;
    }

    // Display turned off
    display_register.status = false;

    // Vertical addressing mode
    display_register.addressing_mode = 0x00;

    // Display not inverted
    display_register.inverted = false;

    return display_register;
}

void fillScreen(SDL_Renderer *renderer,int color) {
    SDL_Rect blackrect;
    blackrect.x = 0;
    blackrect.y = 0;
    blackrect.w = SCREEN_WIDTH;
    blackrect.h = SCREEN_HEIGHT;

    if (color == 0) {
        SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,128);
    } else if (color == 1) {
        SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,128);
    }

    SDL_RenderFillRect(renderer,&blackrect);
    SDL_RenderPresent(renderer);
}

void drawBuffer(ssd1306_register display_register,SDL_Renderer *renderer,uint8_t *buffer) {
    SDL_RenderClear(renderer);

    int x_pos = 0;
    int y_byte = 0;

    for (int i = 0; i < BUFFER_SIZE; ++i) {
        if (x_pos == SSD1306_WIDTH) {
            x_pos = 0;
            y_byte++;
        }

        // One byte = 8 pixels (vertical)
        for (int y = 7; y >= 0; --y) {
            if ((buffer[i] >> y) & 0x01 && display_register.status && !display_register.inverted) {
                drawPixel(renderer,x_pos,y_byte*8+y);
            }
            if (!((buffer[i] >> y) & 0x01) && display_register.status && display_register.inverted) {
                drawPixel(renderer,x_pos,y_byte*8+y);
            }
        }

        x_pos++;
    }

    SDL_RenderPresent(renderer);
}

void drawPixel(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect pixel;
    pixel.x = x;
    pixel.y = y;
    pixel.w = 1;
    pixel.h = 1;

    switch (SCREEN_TYPE) {
        case SCREEN_BLUE:
            SDL_SetRenderDrawColor(renderer,0x10,0xF0,0xFF,128);
            break;
        case SCREEN_BLUE_YELLOW:
            if (y <= 16) {
                SDL_SetRenderDrawColor(renderer,0xFF,0xFD,0x7F,128);
            } else if (y > 17) {
                SDL_SetRenderDrawColor(renderer,0x10,0xF0,0xFF,128);
            } else if (y == 17) {
                SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,128);
            }
            break;
        default:
            SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,128);
            break;
    }

    SDL_RenderFillRect(renderer,&pixel);
}