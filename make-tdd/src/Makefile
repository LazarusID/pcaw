
include ../framework/platform.mk

ARDUINOLIB=-L../framework -larduino
ASSEMBLY_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -lm

USBPORT=/dev/cu.usbmodem1421

# Magic Variables
CFLAGS=-g -I../machine $(ARDUINO_CFLAGS)
CXXFLAGS=-g $(ARDUINO_CXX_FLAGS)
VPATH=../machine

SRC=$(wildcard *.c)
BASE=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASE))

MACHINE_SRC=$(wildcard ../machine/*.c)
MACHINE_BASE=$(basename $(MACHINE_SRC))
MACHINE_OBJS=$(addsuffix .o, $(MACHINE_BASE))

motorcontroller: $(OBJS) $(MACHINE_OBJS)
	$(CC) $(ASSEMBLY_FLAGS) $(OBJS) $(MACHINE_OBJS) -o $@ $(ARDUINOLIB)

motorcontroller.hex: motorcontroller
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

upload: motorcontroller.hex
	$(AVRDUDE) -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P$(USBPORT) -b57600 -D -Uflash:w:motorcontroller.hex:i

clean:
	rm -f motorcontroller
	rm -f motorcontroller.hex
	rm -f *.o
	rm -f *.d
