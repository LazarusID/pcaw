
.PHONY: all clean mock test src package

PACKAGE=my-awesome-arduino-project
VERSION=1.0

all: src

package: clean
	zip -r $(PACKAGE)-$(VERSION).zip . -x .git/\*

clean:
	make -C mock clean
	make -C test clean
	make -C src clean
	rm -f *.zip

mock:
	make -C mock

test: mock
	make -C test

src: test
	make -C src