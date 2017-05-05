CC=clang
CFLAGS=-I./blocksruntime -fblocks
LDFLAGS=-lpthread
OBJS= thpool.o example.o data.o runtime.o

example: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

thpool.o: thpool.c
	$(CC) -c $(CFLAGS) thpool.c

example.o: example.c
	$(CC) -c $(CFLAGS) example.c

data.o: blocksruntime/BlocksRuntime/data.c
	$(CC) -o data.o $(CFLAGS) -c blocksruntime/BlocksRuntime/data.c

runtime.o: blocksruntime/BlocksRuntime/runtime.c
	$(CC) -o runtime.o $(CFLAGS) -c blocksruntime/BlocksRuntime/runtime.c

clean:
	rm -f example $(OBJS)
