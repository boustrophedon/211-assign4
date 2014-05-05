CC=clang
CFLAGS=-g -std=c99 -Wall -Werror -Weverything -Wno-padded
LDFLAGS=-g

all: c-sim

c-sim: cache_sim.o cache_util.o
		$(CC) $(LDFLAGS) cache_sim.o cache_util.o -o c-sim

cache_sim.o: cache_sim.c
		$(CC) $(CFLAGS) -c cache_sim.c

cache_util.o: cache_util.c
		$(CC) $(CFLAGS) -c cache_util.c
		

clean:
	rm c-sim *.o
