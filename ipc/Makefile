
CC=clang
CFLAGS=-Wall -g


BINS=signals msgpassingclient msgpassingserver shmem shmem2 named_pipe_sender named_pipe_recver socket_server

all: $(BINS)


%: %.c
	$(CC) $(CFLAGS) -o $@ $?

	
clean:
	$(RM) $(BINS)
	$(RM) -r *.dSYM


