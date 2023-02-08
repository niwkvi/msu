#include <stdio.h>
#include <stdlib.h>
#include "os_mem.h"

int main()
{
	memory_manager_t mm;
	setup_memory_manager(&mm);

	mm.create(100, 1);
	mm.alloc(30);
	mm.alloc(50);
	mm.alloc(15);
	mm.get_max_block_size();
	mm.get_free_space();
	mm.print_blocks();
	mm.destroy();

	return 0;
}