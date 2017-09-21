ARDUINO_BASE=/Applications/Arduino.app/Contents/Java/hardware
ARDUINO_FIRMWARE=$(ARDUINO_BASE)/arduino/avr
ARDUINO_CORE=$(ARDUINO_FIRMWARE)/cores/arduino
ARDUINO_EIGHT_ANALOG_INPUTS=$(ARDUINO_FIRMWARE)/variants/eightanaloginputs
ARDUINO_TOOLS=$(ARDUINO_BASE)/tools/avr
ARDUINO_BIN=$(ARDUINO_TOOLS)/bin

CC=$(ARDUINO_BIN)/avr-gcc
CXX=$(ARDUINO_BIN)/avr-g++
LINKER=$(ARDUINO_BIN)/avr-gcc-ar
OBJCOPY=$(ARDUINO_BIN)/avr-objcopy
AVRDUDE=$(ARDUINO_BIN)/avrdude

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
VPATH=../machine:$(ARDUINO_CORE)

CORE_C_SRC=$(wildcard $(ARDUINO_CORE)/*.c)
CORE_C_NOTDIR=$(notdir $(CORE_C_SRC))
CORE_C_BASE=$(basename $(CORE_C_NOTDIR))
CORE_C=$(addsuffix .o, $(CORE_C_BASE))

CORE_CPP_SRC=$(wildcard $(ARDUINO_CORE)/*.cpp)
CORE_CPP_NOTDIR=$(notdir $(CORE_CPP_SRC))
CORE_CPP_BASE=$(basename $(CORE_CPP_NOTDIR))
CORE_CPP=$(addsuffix .o, $(CORE_CPP_BASE))

libwiring.a: $(CORE_C) $(CORE_CPP)
	$(LINKER) rcs $@ $^

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d
