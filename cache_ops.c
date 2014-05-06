#include <stdlib.h>
#include <stdio.h>

#include "cache_sim.h"
#include "cache_init.h"
#include "cache_ops.h"
#include "cache_util.h"

cache_set* cache_get_line_index(Cache *cache, int addr, size_t *set_i, size_t *line_i) {
	size_t set_index;
	int tag;
	if (cache->assoc == DIRECT) {
		set_index = extract_set_index(cache, addr);
		tag = extract_tag(cache, addr);
	}
	else if (cache->assoc == FULL_ASSOC) {
		set_index = 0;
		tag = extract_tag(cache, addr);
	}
	else { // n-assoc
		set_index = extract_set_index(cache, addr);
		tag = extract_tag(cache, addr);
	}
	
	cache_set *cur_set = cache->sets[set_index];
	size_t line_index = get_line_index(cur_set, tag);

	*set_i = set_index;
	*line_i = line_index;

	return cur_set;
}

void cache_read(Cache *cache, int pc, int addr) {
	size_t set_index;
	size_t line_index;
	cache_set *cur_set = cache_get_line_index(cache, addr, &set_index, &line_index);
	if (line_index > cur_set->capacity) {
		cache_read_miss(cache, pc, addr, cur_set);
	}
	else {
		cache_read_hit(cache, pc, addr, cur_set);
	}
}

void cache_read_miss(Cache *cache, int pc, int addr, cache_set *cur_set) {
}

void cache_read_hit(Cache *cache, int pc, int addr, cache_set *cur_set) {
}

void cache_write(Cache *cache, int pc, int addr) {
	size_t set_index;
	size_t line_index;
	cache_set *cur_set = cache_get_line_index(cache, addr, &set_index, &line_index);
	if (line_index > cur_set->capacity) {
		cache_write_miss(cache, pc, addr, cur_set);
	}
	else {
		cache_write_hit(cache, pc, addr, cur_set);
	}
}

void cache_write_miss(Cache *cache, int pc, int addr, cache_set *cur_set) {
}

void cache_write_hit(Cache *cache, int pc, int addr, cache_set *cur_set) {
}
