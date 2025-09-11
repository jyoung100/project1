
CC=clang
CFLAGS=-Wall -g
BINS=pthreadex pthreadex2


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ -pthread


clean:
	rm -rf $(BINS) *.o *.dSYM
