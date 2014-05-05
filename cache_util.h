#ifndef CACHE_UTIL_H
#define CACHE_UTIL_H

#include <stddef.h>
#include "cache_sim.h"

char* read_file(char filename[]);
char* get_next_line(char *text, size_t *start);

void compute_masks(Cache *cache);

int extract_set_index(Cache *cache, int addr);
int extract_tag(Cache *cache, int addr);

#endif
