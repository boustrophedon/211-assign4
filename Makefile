CC=clang
CFLAGS=-g -std=c99 -Wall -Werror -Weverything -Wno-padded -Wno-bad-function-cast -Wno-unused-parameter
LDFLAGS=-g -lm

all: c-sim

c-sim: cache_sim.o cache_init.o cache_ops.o cache_util.o
		$(CC) $(LDFLAGS) cache_sim.o cache_init.o cache_ops.o cache_util.o -o c-sim

cache_sim.o: cache_sim.c
		$(CC) $(CFLAGS) -c cache_sim.c

cache_init.o: cache_init.c
		$(CC) $(CFLAGS) -c cache_init.c

cache_ops.o: cache_ops.c
		$(CC) $(CFLAGS) -c cache_ops.c

cache_util.o: cache_util.c
		$(CC) $(CFLAGS) -c cache_util.c
		

clean:
	rm c-sim *.o
