#ifndef CACHE_INIT_H
#define CACHE_INIT_H

#include "cache_sim.h"

Cache* cache_create(void);
void cache_delete(Cache *cache);

cache_set *cache_set_create(size_t num_lines);
void cache_set_delete(cache_set *c_set);

cache_line zeroed_cache_line(void);



#endif
