name: title
count: false
# Building Arduino Programs with Makefiles
<img src="BoxJointGlueUp.png" width="90%" />
---
name: whatdoesittake
# What Does It Take

 - A Native Build Tool (make)

   We need a tool to manage all of the dependencies and reliably repeat all of the steps.

--
count: false
 - A cross compiling tool chain
   - Compiler
   - Assembler
   - Linker
   - Archiver

--
count: false
 - avrdude 
 
   Communicates with the microprocessor

--
count: false
 - Patience

   C development can be challenging.  Cross compiling adds complexity to an already challenging task.

---
name: gettingtools
# Getting the Tools

Two Options
 - Install avr-gcc toolchain for your OS
   - Powerful
   - Tied to your native build system

 - Plaigiarism for Fun and Profit: steal it from Arduino
   - Reduces external dependencies
   - Reduced flexibility
---
name: omgmakefiles
# OMG Makefiles

 - WTF? My CS Classes Never Covered This.

   *Even experienced devs get freaked out.*

--
count: false
 - Actually Simple.
   
   *So is gravity.*
   
   *But using it to calculate something gave us the Integral and Differential Calculus.*
---
name: whatsinamakefile
class: middle
# What's In a Makefile

 - Basically shell scripts with dependency management
   - Target defines what you want to build
   - Dependencies list the parts you need to build first
   - Instructions say what to do with the bits to make the target
---
name: simple_makefile
# Simple Makefile
```makefile
SRC=$(wildcard *.c)
BASES=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASES))

CFLAGS=-g -I../machine -I../src

libmocksystem.a: $(OBJS)
	ar rc $@ $^

clean:
	rm -f *.o
	rm -f *.a
```
---
# OMG WTF
```makefile

include ../framework/platform.mk

ARDUINOLIB=-L../framework -larduino
ASSEMBLY_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -lm

USBPORT=/dev/cu.usbmodem1421

# Magic Variables
CFLAGS=-g -I../machine $(ARDUINO_CFLAGS)
CXXFLAGS=-g $(ARDUINO_CXX_FLAGS)
VPATH=../machine

# Application Source
SRC=$(wildcard *.c)
BASE=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASE))

# Device Specific Source
MACHINE_SRC=$(wildcard ../machine/*.c)
MACHINE_BASE=$(basename $(MACHINE_SRC))
MACHINE_OBJS=$(addsuffix .o, $(MACHINE_BASE))
```
---
# OMG WTF (cont)
```makefile
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
```
---
class: center middle
# Let's See It Work