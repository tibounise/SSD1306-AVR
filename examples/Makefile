CC = g++ -O2 -Wall
TARGET = example1
OBJS = main.o ../simulator/I2C.o ../SSD1306.o ../Framebuffer.o

all: example1

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET) -D SSD1306_SIMULATOR

%.o: %.cpp %.c
	$(CC) -c $< -D SSD1306_SIMULATOR -Wc++11-extensions

clean:
	rm $(TARGET) $(OBJS)