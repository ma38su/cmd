CFLAGS=-Wall -std=c11 -g -static
SRCS=stdio_cat.c
OBJS=stdio_cat.o
#SRCS=$(wildcard *.c)
#OBJS=$(SRCS:.c=.o)

stdio: stdio_cat.c
	$(CC) -o cat stdio_cat.c $(LDFLAGS)

sys: sys_cat.c
	$(CC) -o cat sys_cat.c $(LDFLAGS)

clean:
	rm -f cat *.s *.o *~ tmp/* .*.c

.PHONY: test clean
