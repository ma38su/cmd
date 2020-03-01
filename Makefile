CFLAGS=-Wall -std=c11 -g -static

all: cat fcat wc head tail ls mkdir

cat: cat.c
	$(CC) -o cat cat.c $(LDFLAGS)
fcat: fcat.c
	$(CC) -o fcat fcat.c $(LDFLAGS)
wc: wc.c
	$(CC) -o wc wc.c $(LDFLAGS)

head: head.c
	$(CC) -o head head.c $(LDFLAGS)

tail: tail.c
	$(CC) -o tail tail.c $(LDFLAGS)

ls: ls.c
	$(CC) -o ls ls.c $(LDFLAGS)

mkdir: mkdir.c
	$(CC) -o mkdir mkdir.c $(LDFLAGS)


clean:
	rm -f cat fcat wc head tail ls *.s *.o *~ tmp/* .*.c

.PHONY: test clean
