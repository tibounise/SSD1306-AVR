ARCH = SIMULATOR

# MCU specific
MCU = atmega328p
F_CPU = 16000000

CXX_SIMULATOR = g++
CXX_AVR = avr-g++
CXX = $(CXX_$(ARCH))

CXXFLAGS_SIMULATOR = -O2 -Wall -D SIMULATOR
CXXFLAGS_AVR = -Os -Wall -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I./include -I/usr/lib/avr/include -fno-exceptions
CXXFLAGS = $(CXXFLAGS_$(ARCH))

OBJS_SIMULATOR = ../../simulator/I2C.o ../../SSD1306.o ../../Framebuffer.o example2.o
OBJS_AVR = ../../I2C.o ../../SSD1306.o ../../Framebuffer.o example2.o
OBJS = $(OBJS_$(ARCH))

TARGET_SIMULATOR = example2
TARGET_AVR = example2.hex
TARGET = $(TARGET_$(ARCH))

all: $(TARGET)

%.hex: %.obj
	avr-objcopy -R .eeprom -O ihex $< $@

%.obj: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $@

ifeq ($(ARCH),SIMULATOR)
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET) -D SIMULATOR
endif

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all $(TARGET) clean