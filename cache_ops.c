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
		cache_read_hit(cache, pc, addr, cur_set, line_index);
	}
}

void cache_read_miss(Cache *cache, int pc, int addr, cache_set *cur_set) {
	cache->memory_reads +=1;
	cache->cache_misses +=1;
	size_t empty = find_empty_line(cur_set);
	if (empty > cur_set->capacity) {
		size_t evict = find_lowest_lru_line(cur_set);
		if (cache->write_policy == WRITEBACK) {
			if (cur_set->lines[evict].dirty == 1) {
				cache->memory_writes += 1;
				cur_set->lines[evict].dirty = 0;
			}
			cur_set->lines[evict].lru_counter = pc;
			cur_set->lines[evict].tag = extract_tag(cache, addr);
		}
		else {
			cur_set->lines[evict].lru_counter = pc;
			cur_set->lines[evict].tag = extract_tag(cache, addr);
		}
	}
	else {
		cur_set->lines[empty].valid = 1;
		cur_set->lines[empty].lru_counter = pc;
		cur_set->lines[empty].tag = extract_tag(cache, addr);
	}
}

void cache_read_hit(Cache *cache, int pc, int addr, cache_set *cur_set, size_t line_index) {
	cache->cache_hits +=1;
	cur_set->lines[line_index].lru_counter = pc;
}

void cache_write(Cache *cache, int pc, int addr) {
	size_t set_index;
	size_t line_index;
	cache_set *cur_set = cache_get_line_index(cache, addr, &set_index, &line_index);
	if (line_index > cur_set->capacity) {
		cache_write_miss(cache, pc, addr, cur_set);
	}
	else {
		cache_write_hit(cache, pc, addr, cur_set, line_index);
	}
}

void cache_write_miss(Cache *cache, int pc, int addr, cache_set *cur_set) {
	cache->cache_misses +=1;
	cache->memory_reads +=1;
	size_t empty = find_empty_line(cur_set);
	if (empty < cur_set->capacity) {
		cur_set->lines[empty].valid = 1;
		cur_set->lines[empty].lru_counter = pc;
		cur_set->lines[empty].tag = extract_tag(cache, addr);
		cur_set->lines[empty].dirty = 1;
	}
	else {
		size_t evict = find_lowest_lru_line(cur_set);
		if (cache->write_policy == WRITEBACK) {
			if (cur_set->lines[evict].dirty == 1) {
				cache->memory_writes+=1;
			}
			cur_set->lines[evict].lru_counter = pc;
			cur_set->lines[evict].tag = extract_tag(cache, addr);
			cur_set->lines[evict].dirty = 1;
		}
		else {
			cache->memory_writes+=1;
			cur_set->lines[evict].lru_counter = pc;
			cur_set->lines[evict].tag = extract_tag(cache, addr);
		}
	}
}

void cache_write_hit(Cache *cache, int pc, int addr, cache_set *cur_set, size_t line_index) {
	cache->cache_hits +=1;
	if (cache->write_policy == WRITETHRU) {
		cache->memory_writes+=1;
	}
	else {
		if (cur_set->lines[line_index].dirty == 1) {
			cache->memory_writes+=1;
		} 
		cur_set->lines[line_index].dirty = 1;
		cur_set->lines[line_index].tag = 1;
	}
}
