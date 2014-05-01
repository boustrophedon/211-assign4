CC=clang
CFLAGS=-ansi -pedantic -Wall -Werror
LDFLAGS=

all: c-sim

c-sim: cache_sim.o
		$(CC) $(LDFLAGS) cache_sim.o -o example

cache_sim.o: cache_sim.c
		$(CC) $(CFLAGS) -c cache_sim.c

