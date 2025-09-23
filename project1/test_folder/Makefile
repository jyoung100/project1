
CC=gcc
CFLAGS=-Wall -g

BINS= mem_shim.so leakcount  


all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $?

mem_shim.so: mem_shim.c
	$(CC) $(CFLAGS) -shared -fPIC mem_shim.c -o mem_shim.so -ldl

clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
