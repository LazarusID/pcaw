SRC=$(wildcard *.c)
BASES=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASES))

CFLAGS=-g


libmocksystem.a: $(OBJS)
	ar rc $@ $^

clean:
	rm -f *.o
	rm -f *.a

