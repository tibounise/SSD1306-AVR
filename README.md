# SSD1306-AVR

SSD1306-AVR is a C++ library for using SSD1306, 128x64, monochrome OLED displays. Currently only the I2C version of the display is supported.

The I2C of the display is set up in SSD1306.h :
```C
#define SSD1306_DEFAULT_ADDRESS 0x78
```

The library is written in pure C++. You'll only need avr-libc, Arduino framework is not needed.

## Example code

```C++
#include <stdint.h>
#include "SSD1306.h"

int main(void) {
    // This is our buffer
    // Each byte = 8 pixels on the screen
    uint8_t buffer[1024];

    // Only two lines of code to initiate the driver
    // and to send our framebuffer
    SSD1306 myDisplay;
    myDisplay.sendFramebuffer(buffer);

    // Hardware function to reverse the pixels
    // (swap black and white pixel)
    myDisplay.invert(1);
    // Revert back to normal display
    myDisplay.invert(0);

    return 0;
}
```