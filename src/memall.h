#ifndef MEMALL_H_
#define MEMALL_H_

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEAP_CAP_BYTES 640000
#define HEAP_CAP_WORDS (HEAP_CAP_BYTES / sizeof(uintptr_t))
#define CHUNK_LIST_CAP 1024

#define UNIMPLEMENTED \
	do { \
		fprintf(stderr, "%s:%d: %s is not implemented yet\n", \
			__FILE__, __LINE__, __func__); \
		abort(); \
	} while(0)

typedef struct {
	uintptr_t *start;
	size_t size;
} Chunk;

typedef struct {
	size_t count;
	Chunk chunks[CHUNK_LIST_CAP];
} Chunk_List;

extern Chunk_List alloced_chunks;
extern Chunk_List freed_chunks;
extern uintptr_t heap[HEAP_CAP_WORDS];
extern const uintptr_t *stack_base;

void *heap_alloc(size_t size);
void heap_free(void *ptr);
void heap_collect(void);

// impruvable in lesser O
int chunk_list_find(const Chunk_List *list, uintptr_t *ptr);
void chunk_list_insert(Chunk_List *list, void *ptr, size_t size);
void chunk_list_remove(Chunk_List *list, size_t index);
void chunk_list_merge(Chunk_List *dst, const Chunk_List *src);
void chunk_list_dump(const Chunk_List *list);

#endif // MEMALL_H_
