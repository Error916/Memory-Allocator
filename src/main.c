#include <stdio.h>

#include "memall.h"

extern Chunk_List alloced_chunks;
extern Chunk_List freed_chunks;

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

	for(size_t i = 0; i < 10; ++i){
		void *p = heap_alloc(i);
		if(i % 2 == 0){
			heap_free(p);
		}
	}

	chunk_list_dump(&alloced_chunks);
	chunk_list_dump(&freed_chunks);

	return 0;
}
