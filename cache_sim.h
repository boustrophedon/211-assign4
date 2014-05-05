#ifndef CACHE_SIM_H
#define CACHE_SIM_H

#include <stddef.h>

#define DIRECT 1
#define FULL_ASSOC 0
 
#define WRITEBACK 0
#define WRITETHRU 1

typedef struct cache_line {
	int tag;
	int lru_counter;
	int dirty; // for write-back
	int valid; // if not written to yet. i'm not sure if this ever gets unset
	// actual block data is not simulated
} cache_line;

typedef struct cache_set {
	cache_line *lines;
	size_t capacity;
} cache_set;

typedef struct cache_ {
	cache_set **sets;
	int cache_size;
	int assoc;
	int block_size;
	int write_policy;
	size_t num_sets;
	int set_mask; // not actually masks in the sense that we bitwise and
	int tag_mask; // but they serve the same purpose. we just do integer division.
} Cache;


extern int cache_size;
extern int assoc;
extern int block_size;
extern int write_policy;
extern char *tfile_name;

extern Cache *global_cache;

void parse_arguments(char *argv[]);
void parse_file(char *text);
void parse_line(char *line);


#endif
