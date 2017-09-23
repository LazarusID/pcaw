
include ../framework/platform.mk


WIRINGLIB=-L../framework -lwiring

ARDUINO_CFLAGS=-Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 \
	-DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	-I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CFLAGS=-g -I../machine $(ARDUINO_CFLAGS)

ARDUINO_CXX_FLAGS=-Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p \
	-DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	 -I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)
CXXFLAGS=-g $(ARDUINO_CXX_FLAGS)

ASSEMBLY_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -lm

USBPORT=/dev/cu.usbmodem1421
VPATH=../machine

SRC=$(wildcard *.c)
BASE=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASE))

MACHINE_SRC=$(wildcard ../machine/*.c)
MACHINE_BASE=$(basename $(MACHINE_SRC))
MACHINE_OBJS=$(addsuffix .o, $(MACHINE_BASE))

motorcontroller: $(OBJS) $(MACHINE_OBJS)
	$(CC) $(ASSEMBLY_FLAGS) $(OBJS) $(MACHINE_OBJS) -o $@ $(WIRINGLIB)

motorcontroller.hex: motorcontroller
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

upload: motorcontroller.hex
	$(AVRDUDE) -C/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P$(USBPORT) -b57600 -D -Uflash:w:motorcontroller.hex:i

clean:
	rm -f motorcontroller
	rm -f motorcontroller.hex
	rm -f *.o
	rm -f *.d
