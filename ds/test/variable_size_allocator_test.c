
#include <stdio.h>

#include "variable_size_allocator.h"

void Test(void)
{
	size_t space = 200;
	void* pool = (void*)malloc(space);
	VSAInit(pool, space);
	
	
	free(space);
}

int main()
{
	
	return 0;
}
