#ifndef CACHE_SIM_H
#define CACHE_SIM_H

#define DIRECT -1
#define FULL_ASSOC 0
 
#define WRITEBACK 0
#define WRITETHRU 1

typedef struct cache_line {
	int tag;
	int index;
	int lru_counter;
	int dirty; // for write-back
	int valid; // if not written to yet. i'm not sure if this ever gets unset
	// actual block data is not simulated
} cache_line;

typedef struct cache_set {
	cache_line *lines;
	int capacity;
} cache_set;

typedef struct cache_ {
	cache_set *sets;
	int cache_size;
	int assoc;
	int block_size;
	int write_policy;
} Cache;


extern int cache_size;
extern int assoc;
extern int block_size;
extern int write_policy;
extern char *tfile_name;

extern Cache cache;

void parse_arguments(char *argv[]);
void parse_file(char *text);
void parse_line(char *line);


#endif
