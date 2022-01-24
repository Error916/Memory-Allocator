#include <stdio.h>

#include "memall.h"

typedef struct node {
	char x;
	struct node *left;
	struct node *right;
} Node;

Node *generate_tree(size_t cur_lvl, size_t max_lvl){
	if(cur_lvl < max_lvl){
		Node *root = heap_alloc(sizeof(*root));
		assert((char) cur_lvl - 'a' <= 'z');
		root->x = cur_lvl + 'a';
		root->left = generate_tree(cur_lvl + 1, max_lvl);
		root->right = generate_tree(cur_lvl + 1, max_lvl);
		return root;
	} else {
		return NULL;
	}
}

void print_tree(Node *root, size_t cur_lvl){
	if(root != NULL){
		printf("value: %c \n", root->x);
		for(size_t i = 0; i < cur_lvl; ++i) printf("\t");

		printf("left: ");
		print_tree(root->left, cur_lvl + 1);
		printf("\n");
		for(size_t i = 0; i < cur_lvl; ++i) printf("\t");

		printf("right: ");
		print_tree(root->right, cur_lvl + 1);
	} else {
		printf("NULL ");
	}
}

#define N 10

void * ptrs[N] = {0};

int main(int argc, char **argv){

	(void) argc;
	(void) argv;

	stack_base = (const uintptr_t *) __builtin_frame_address(0);

	Node *root = generate_tree(0, 3);

	print_tree(root, 0);
	printf("\n\n");

	printf("-----------------------\n");
	heap_collect();
	chunk_list_dump(&alloced_chunks);
	chunk_list_dump(&freed_chunks);

	printf("-----------------------\n");
	root = NULL;
	heap_collect();
	chunk_list_dump(&alloced_chunks);
	chunk_list_dump(&freed_chunks);

	return 0;
}
