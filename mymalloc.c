#include "mymalloc.h"

#define MEMORY_SIZE 25000

static char memory[MEMORY_SIZE];

typedef struct Block{
	size_t size;
	struct Block *next;
}Block;

static Block *free_ptr = NULL;

void initialize_memory() {
    free_ptr = (Block *)memory;
    free_ptr->size = MEMORY_SIZE - sizeof(Block);
    free_ptr->next = NULL;
}
void *MyMalloc(size_t size) {
    if (size == 0 || size > MEMORY_SIZE) {
        return NULL;  
    }

    
    size = (size + sizeof(Block) - 1) / sizeof(Block) * sizeof(Block);

    Block *current_block = free_ptr;
    Block *prev_block = NULL;

    while (current_block != NULL) {
        if (current_block->size >= size) {
            if (current_block->size > size + sizeof(Block)) {
                
                Block *new_block = (Block *)((char *)current_block + size);
                new_block->size = current_block->size - size - sizeof(Block);
                new_block->next = current_block->next;
                current_block->size = size;
                current_block->next = new_block;
            }

            
            free_ptr = current_block->next;
            return (char *)current_block + sizeof(Block);
        }

        prev_block = current_block;
        current_block = current_block->next;
    }

    
    return NULL;
}


void MyFree(void *ptr) {
    if (ptr == NULL) {
        return;  
    }

    Block *block_to_free = (Block *)((char *)ptr - sizeof(Block));
    block_to_free->next = free_ptr;
    free_ptr = block_to_free;
}









