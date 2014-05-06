#ifndef CACHE_UTIL_H
#define CACHE_UTIL_H

#include <stddef.h>
#include "cache_sim.h"

char* read_file(char filename[]);
char* get_next_line(char *text, size_t *start);

void compute_masks(Cache *cache);

size_t extract_set_index(Cache *cache, int addr);
int extract_tag(Cache *cache, int addr);

size_t get_line_index(cache_set *set, int tag); 

size_t find_empty_line(cache_set *set);
size_t find_lowest_lru_line(cache_set *set);

#endif
