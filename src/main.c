#include <stdio.h>

#include "memall.h"

extern Chunk_List alloced_chunks;
extern Chunk_List freed_chunks;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

	void *p[10];

	for(size_t i = 0; i < 10; ++i){
		p[i] = heap_alloc(i);
	}

	for(size_t i = 0; i < 10; ++i){
		heap_free(p[i]);
	}

	heap_alloc(10);

	chunk_list_dump(&alloced_chunks);
	chunk_list_dump(&freed_chunks);

	return 0;
}
