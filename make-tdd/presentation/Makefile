
all: make-builds.html tdd.html

clean:
	rm -f make-builds.html tdd.html

make-builds.html: make-builds.md
	cat prefix.html > $@
	cat $^ >> $@
	cat suffix.html >> $@

tdd.html: tdd.md
	cat prefix.html > $@
	cat $^ >> $@
	cat suffix.html >> $@

