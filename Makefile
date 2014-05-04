CC=clang
CFLAGS=-std=c99 -Wall -Werror
LDFLAGS=

all: c-sim

c-sim: cache_sim.o
		$(CC) $(LDFLAGS) cache_sim.o -o c-sim

cache_sim.o: cache_sim.c
		$(CC) $(CFLAGS) -c cache_sim.c

clean:
	rm c-sim *.o
