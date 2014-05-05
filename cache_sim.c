#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache_sim.h"
#include "cache_init.h"
#include "cache_ops.h"
#include "cache_util.h"

int cache_size;
int assoc;
int block_size;
int write_policy;

char *tfile_name;

Cache *global_cache; // this is dumb but I have a deadline so whatever. 

// wouldn't it be nice to have a library to do this for me. sigh.
void parse_arguments(char *argv[]) {
	cache_size = atoi(argv[1]);

	if (strcmp(argv[2], "direct") == 0) {
		assoc = DIRECT;
	}
	else if (strncmp(argv[2], "assoc", 5) == 0) {
		if (strlen(argv[2]) == 5) {
			assoc = FULL_ASSOC;
		}
		// assoc:n
		// could check for the : at argv[2][5] but whatever
		else {
			assoc = atoi(argv[2]+6); //+6 gives us a string starting at one past the :
		}
	}

	block_size = atoi(argv[3]);

	if (strcmp(argv[4], "wb") == 0) {
		write_policy = WRITEBACK;
	}
	else {
		write_policy = WRITETHRU;
	}

	tfile_name = malloc(sizeof(char)*strlen(argv[5]) +1);
	strcpy(tfile_name, argv[5]);
}

void parse_file(char *text) {
	size_t pos = 0;
	char *line = get_next_line(text, &pos);
	while (line != NULL) {
		if (line == NULL) {
			break;
		}
		else if (strcmp(line, "#eof") == 0) {
			free(line);
			break;
		}
		else {
			parse_line(line);
			free(line);
			line = NULL;
			line = get_next_line(text, &pos);
		}
	}
	return;
}

void parse_line(char *line) {
	int pc;
	char wr;
	int loc;
	sscanf(line, "%x: %c %x", &pc, &wr, &loc);
	return;
}

int main(int argc, char *argv[]) {
	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0) {
			printf("Help text goes here\n");
			return 0;
		}
	}
	else if (argc != 6) {
		printf("Incorrect number of arguments.\n");
		return -1;
	}

	parse_arguments(argv);
	char *text = read_file(tfile_name);
	if (text == NULL) {
		printf("exiting.\n");
		return -1;
	}

	global_cache = cache_create();

	parse_file(text);

	cache_delete(global_cache);
	free(tfile_name);
	free(text);
	return 0;
}
