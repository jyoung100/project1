
CC=clang
CFLAGS=-Wall -g

BINS=mystery mystery2 mystery3 mystery4 shim.so shimtest envtest envdemo variadic


all: $(BINS)

mystery: mystery.c
	$(CC) $(CFLAGS) -o mystery mystery.c

mystery2: mystery2.c
	$(CC) $(CFLAGS) -o mystery2 mystery2.c

mystery3: mystery3.c
	$(CC) $(CFLAGS) -o mystery3 mystery3.c

mystery4: mystery4.c
	$(CC) $(CFLAGS) -o mystery4 mystery4.c

%: %.c
	$(CC) $(CFLAGS) -o $@ $?

shim.so: shim.c
	$(CC) $(CFLAGS) -shared -fPIC shim.c -o shim.so -ldl

clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM
