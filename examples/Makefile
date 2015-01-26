CXX = g++
CXXFLAGS += -D SIMULATOR -O2 -Wall
TARGET = example1
OBJS = ../simulator/I2C.o ../SSD1306.o ../Framebuffer.o example1.o

all: example1

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET) -D SIMULATOR

%.o: %.cpp %.c
	$(CC) -c $< -D SIMULATOR

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all example1 clean