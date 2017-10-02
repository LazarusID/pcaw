ARDUINO_BASE=/Applications/Arduino.app/Contents/Java/hardware
ARDUINO_FIRMWARE=$(ARDUINO_BASE)/arduino/avr
ARDUINO_CORE=$(ARDUINO_FIRMWARE)/cores/arduino
ARDUINO_EIGHT_ANALOG_INPUTS=$(ARDUINO_FIRMWARE)/variants/eightanaloginputs
ARDUINO_TOOLS=$(ARDUINO_BASE)/tools/avr
ARDUINO_BIN=$(ARDUINO_TOOLS)/bin

# Special definitions used by the Arduino library
ARDUINO_CFLAGS=-Os -w -std=gnu11 -ffunction-sections -fdata-sections \
	-MMD -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 \
	-DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	-I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)

ARDUINO_CXX_FLAGS=-Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p \
	-DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  \
	-I$(ARDUINO_CORE) -I$(ARDUINO_EIGHT_ANALOG_INPUTS)

CC=$(ARDUINO_BIN)/avr-gcc
CXX=$(ARDUINO_BIN)/avr-g++
LINKER=$(ARDUINO_BIN)/avr-gcc-ar
OBJCOPY=$(ARDUINO_BIN)/avr-objcopy
AVRDUDE=$(ARDUINO_BIN)/avrdude