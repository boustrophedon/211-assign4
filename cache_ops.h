#ifndef CACHE_OPS_H
#define CACHE_OPS_H

#include "cache_sim.h"

cache_set* cache_get_line_index(Cache *cache, int addr, size_t *set_i, size_t *line_i);

void cache_read(Cache *cache, int pc, int addr);
void cache_read_miss(Cache *cache, int pc, int addr, cache_set *cur_set);
void cache_read_hit(Cache *cache, int pc, int addr, cache_set *cur_set);

void cache_write(Cache *cache, int pc, int addr);
void cache_write_miss(Cache *cache, int pc, int addr, cache_set *cur_set);
void cache_write_hit(Cache *cache, int pc, int addr, cache_set *cur_set);

#endif
