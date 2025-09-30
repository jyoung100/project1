
CC=gcc
CFLAGS=-Wall -g

BINS=mem_shim.so leakcount sctracer 


all: $(BINS)

leakcount: leakcount.c
	$(CC) $(CFLAGS) -o leakcount leakcount.c

sctracer: sctracer.c
	$(CC) $(CFLAGS) -o sctracer sctracer.c

%: %.c
	$(CC) $(CFLAGS) -o $@ $?

mem_shim.so: mem_shim.c
	$(CC) $(CFLAGS) -shared -fPIC mem_shim.c -o mem_shim.so -ldl

clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
