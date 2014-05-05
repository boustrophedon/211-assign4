#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache_sim.h"

// these should probably go in a header...
#define DIRECT -1
#define FULL_ASSOC 0

#define WRITEBACK 0
#define WRITETHRU 1

int cache_size;
int assoc;
int block_size;
int write_policy;

char *tfile_name;

// no error checking because the assignment said they wouldn't give us bad inputs
// though normally i'd use an actual library to do this. sigh.
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

int main(int argc, char *argv[]) {

	if (strcmp(argv[1], "-h") == 0) {
		printf("Help text goes here\n");
	}
	else {
		parse_arguments(argv);
	}
	printf("%d %d %d %d %s\n", cache_size, assoc, block_size, write_policy, tfile_name);

	return 0;
}
