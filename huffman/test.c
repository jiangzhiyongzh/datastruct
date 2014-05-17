/*************************************************************************
	> File Name: test.c
	> Created Time: 2014年05月15日 星期四 12时22分33秒
 ************************************************************************/

#include <stdio.h>
#include "huffman.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	assert(argc >= 4);

	char *src_name = argv[2];
	char *dest_name = argv[3];

	struct huffman *phf = (struct huffman *)malloc(sizeof(*phf));
	assert(phf != NULL);
	huffman_init(phf);
	if (strcmp(argv[1], "-c") == 0) {
		phf->compress(phf, src_name, dest_name);
	} else if (strcmp(argv[1], "-d") == 0) {
		phf->decompress(phf, src_name, dest_name);
	} else {
		fprintf(stderr, "Usage: %s -c|-d [src_name|dest_name]\n", argv[0]);
	}

	huffman_destroy(phf);
	free(phf);
	return 0;
}
