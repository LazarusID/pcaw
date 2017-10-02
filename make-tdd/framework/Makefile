include platform.mk

ASSEMBLY_FLAGS=-w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -lm

CFLAGS=-g $(ARDUINO_CFLAGS)
CXXFLAGS=-g $(ARDUINO_CXX_FLAGS)
VPATH=$(ARDUINO_CORE)

CORE_C_SRC=$(wildcard $(ARDUINO_CORE)/*.c)
CORE_C_NOTDIR=$(notdir $(CORE_C_SRC))
CORE_C_BASE=$(basename $(CORE_C_NOTDIR))
CORE_C=$(addsuffix .o, $(CORE_C_BASE))

CORE_CPP_SRC=$(wildcard $(ARDUINO_CORE)/*.cpp)
CORE_CPP_NOTDIR=$(notdir $(CORE_CPP_SRC))
CORE_CPP_BASE=$(basename $(CORE_CPP_NOTDIR))
CORE_CPP=$(addsuffix .o, $(CORE_CPP_BASE))

libarduino.a: $(CORE_C) $(CORE_CPP)
	$(LINKER) rcs $@ $^

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d
