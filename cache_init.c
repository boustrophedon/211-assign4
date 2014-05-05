#include <stdlib.h>
#include <stdio.h>

#include "cache_init.h"
#include "cache_sim.h"
#include "cache_util.h"

Cache *cache_create() {
	size_t num_sets;
	size_t num_lines;
	if (assoc == DIRECT) {
		num_lines = 1;
		num_sets = (size_t)(cache_size/block_size);
	}
	else if (assoc == FULL_ASSOC) {
		num_lines = (size_t)(cache_size/block_size);
		num_sets = 1;
	}	
	else {
		num_lines = (size_t)assoc;
		num_sets = (size_t)(cache_size/(block_size*assoc));
	}

	printf("num sets %zu, num lines %zu\n", num_sets, num_lines);

	Cache *new_cache = malloc(sizeof(Cache));
	new_cache->cache_size = cache_size;
	new_cache->assoc = assoc;
	new_cache->block_size = block_size;
	new_cache->write_policy = write_policy;
	new_cache->num_sets = num_sets;
	
	new_cache->sets = malloc(sizeof(cache_set)*num_sets);
	for (size_t i = 0; i < num_sets; i++) {
		new_cache->sets[i] = cache_set_create(num_lines);
	}

	compute_masks(new_cache);

	return new_cache;
}

void cache_delete(Cache *cache) {
	for (size_t i = 0; i < cache->num_sets; i++) {
		cache_set_delete(cache->sets[i]);
	}
	free(cache->sets);
	free(cache);
}

cache_set *cache_set_create(size_t num_lines) {
	cache_set *new_set = malloc(sizeof(cache_set));
	new_set->capacity = num_lines;
	new_set->lines = malloc(sizeof(cache_line)*num_lines);

	for (size_t i = 0; i < num_lines; i++) {
		new_set->lines[i] = zeroed_cache_line();
	}
	
	return new_set;
}

void cache_set_delete(cache_set *c_set) {
	free(c_set->lines);
	free(c_set);
}

// i'm not sure if this is strictly necessary but it's always a good thing to do
cache_line zeroed_cache_line() {
	cache_line line;
	line.tag = 0;
	line.lru_counter = 0;
	line.dirty = 0;
	line.valid = 0;

	return line; // returns a copy of this struct
}
