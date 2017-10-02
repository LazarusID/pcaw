
.PHONY: all clean mock test src package framework unity

PACKAGE=my-awesome-arduino-project
VERSION=1.0

all: src

package: clean
	zip -r $(PACKAGE)-$(VERSION).zip . -x .git/\*

clean:
	make -C mock clean
	make -C test clean
	make -C src clean
	make -C unity clean
	make -C machine clean
	make -C framework clean
	rm -f *.zip

framework:
	make -C framework

unity:
	make -C unity

mock:
	make -C mock

test: mock unity
	make -C src clean
	make -C test

src: test framework
	make -C src