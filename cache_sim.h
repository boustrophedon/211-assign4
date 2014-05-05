#ifndef CACHE_SIM_H
#define CACHE_SIM_H

#define DIRECT -1
#define FULL_ASSOC 0
 
#define WRITEBACK 0
#define WRITETHRU 1

typedef struct cache {
	int cache_size;
	int assoc;
	int block_size;
	int write_policy;
	cache_set *sets;
} cache;

typedef struct cache_set {
	int capacity;
	cache_line *lines;
} cache_set;

typedef struct cache_line {
	int tag;
	int index;
	int lru_counter;
	int dirty; // for write-back
	int valid; // if not written to yet. i'm not sure if this ever gets unset
	// actual block data is not simulated
} cache_line;

#endif
