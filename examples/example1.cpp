#include "example1.h"

int main(void) {
    Framebuffer fb;

    fb.drawRectangle(1,1,126,62);
    fb.drawRectangle(3,3,124,60);
    fb.drawRectangle(5,5,122,58);
    fb.drawRectangle(7,7,120,56);
    fb.drawRectangle(9,9,118,54);
    fb.drawRectangle(11,11,116,52);
    fb.drawRectangle(13,13,114,50);
    
    fb.show();

    // Invert uses direct hardware commands
    // So no need to send the framebuffer again
    // => no need to fb.show();
    fb.invert(1);

    return 0;
}