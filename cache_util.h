#ifndef CACHE_UTIL_H
#define CACHE_UTIL_H
#include <stddef.h>

char* read_file(char filename[]);
char* get_next_line(char *text, size_t *start);

#endif
