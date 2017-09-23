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