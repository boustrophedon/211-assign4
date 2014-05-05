#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "cache_util.h"

char* read_file(char fname[]) {
	FILE* fd = fopen(fname, "r");

	if (fd==NULL) {
		fprintf(stderr, "Couldn't open file.\n");
		return NULL;
	}

	if (fseek(fd, 0, SEEK_END)) {
		fprintf(stderr, "Couldn't seek to end of file.\n");
		return NULL;
	}

	size_t fsize = (size_t)ftell(fd);
	rewind(fd);
	

	char *fstring = malloc(sizeof(char)*(fsize+1));
	if (fstring == NULL) {
		fprintf(stderr, "Couldn't allocate memory for string.\n");
		return NULL;
	}

	fread(fstring, 1, fsize, fd);	
	fclose(fd);

	fstring[fsize] = '\0';

	return fstring;

}

char* get_next_line(char *text, size_t *start) {
	size_t pos = *start;
	size_t end = pos;
	while (text[end] != '\n') {
		if (text[end] == '\0') {
			return NULL;
		}
		end++;
	}
	char *line = malloc((end-pos)*sizeof(char) +1);
	strncpy(line, text+pos, (end-pos));
	line[end-pos] = '\0';

	*start = end+1;
	return line;
}

void compute_masks(Cache *cache) {
	int set_bits = (int)log2(cache->num_sets);
	printf("set bits %d\n", set_bits);

	cache->set_mask = cache->block_size;

	int tag_mask = cache->set_mask;
	for (int i = 0; i<set_bits; i++) {
		tag_mask = tag_mask*2;
	}
	cache->tag_mask = tag_mask;

	return;
}

int extract_set_index(Cache *cache, int addr) {
	return (int)(addr/cache->set_mask)%(int)(cache->num_sets);
}
int extract_tag(Cache *cache, int addr) {
	return (addr/cache->tag_mask);
}
