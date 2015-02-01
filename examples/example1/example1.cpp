#include "example1.h"

int main(void) {
    Framebuffer fb;

    fb.drawRectangle(2,2,125,61);
    fb.drawRectangle(6,6,12,12,1);
    
    fb.show();

    // Invert uses direct hardware commands
    // So no need to send the framebuffer again
    // => no need to fb.show();
    fb.invert(1);

    return 0;
}