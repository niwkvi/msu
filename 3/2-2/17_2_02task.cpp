#include <stdio.h>
#include <stdlib.h>
#include "os_mem.h"

struct Stack
{
    int size = 0;
    int pos = 0;
    Stack* prev_block = NULL;
    Stack* next_block = NULL;
};

bool is_mm_created = false;
int memory = 0;
int cur_free_memory = 0;
int blocks_num = 0;
Stack* cur = NULL;
Stack* first = NULL;

int create(int size, int num_pages)
{
    if (is_mm_created)
        return 0;
    
    memory = size;
    cur_free_memory = size;

    first = (Stack*)malloc(sizeof(Stack));

    if (first == NULL)
        return 0;

    first->size = 0;
    first->pos = 0;
    first->prev_block = NULL;
    first->next_block = NULL;

    cur = first;

    is_mm_created = true;

    return 1;
}

int destroy()
{
    if (!is_mm_created)
        return 0;

    while (cur != first)
    {
        cur = cur->prev_block;
        free(cur->next_block);
        cur->next_block = NULL;
    }

    free(first);
    first = NULL;

    memory = 0;
    cur_free_memory = 0;
    blocks_num = 0;

    is_mm_created = false;

    return 1;
}

mem_handle_t alloc(int block_size)
{
    if (!is_mm_created || cur_free_memory < block_size)
        return mem_handle_t(0, 0);

    int address = memory - cur_free_memory;
    cur_free_memory -= block_size;

    cur->next_block = (Stack*)malloc(sizeof(Stack));

    if (cur->next_block == NULL)
        return mem_handle_t(0, 0);
    
    cur->next_block->size = block_size;
    cur->next_block->pos = cur->pos + cur->size;
    cur->next_block->prev_block = cur;
    cur->next_block->next_block = NULL;

    cur = cur->next_block;
    
    blocks_num++;

    return mem_handle_t(address, block_size);
}

int free(mem_handle_t h)
{
    if (!is_mm_created || cur->size == 0)
        return 0;

    cur_free_memory += cur->size;
    
    cur = cur->prev_block;

    free(cur->next_block);
    cur->next_block = NULL;

    blocks_num--;

    return 1;
}

int get_max_block_size()
{
    if (!is_mm_created)
        return 0;

    return cur_free_memory;
}

int get_free_space()
{
    if (!is_mm_created)
        return 0;

    return cur_free_memory;
}

void print_blocks()
{
    Stack* temp;
    temp = first;

    for (int i = 0; i < blocks_num; i++)
    {
        printf("%d ", temp->next_block->pos);
        printf("%d\n", temp->next_block->size);
        temp = temp->next_block;
    }
}

void setup_memory_manager(memory_manager_t* mm)
{
    mm->create = create;
    mm->destroy = destroy;
    mm->alloc = alloc;
    mm->free = free;
    mm->get_max_block_size = get_max_block_size;
    mm->get_free_space = get_free_space;
    mm->print_blocks = print_blocks;
}