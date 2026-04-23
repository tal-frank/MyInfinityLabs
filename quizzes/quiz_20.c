#include <stddef.h>
#include <stdio.h>

long* SumIntPairsToLong(unsigned int ints[], size_t numOfElements)
{
	size_t i = 0;
	size_t j = 0;
	long* longs = (long*)ints;
	for(i = 0; i < numOfElements; i += 2, ++j)
	{
		longs[j] = ((long)ints[i]) + ((long)ints[i + 1]);
	}
	return longs;
}


int main()
{
	unsigned int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 0xFFFFFFFF, 0xFFFFFFFF};
	size_t size = 10;
	size_t i = 0;
	long* longs = SumIntPairsToLong(ints, size);
	
	for (i = 0; i < (size / 2); ++i)
	{
		printf(" %ld ," , longs[i]);
	}
	printf("\n");
	
	for (i = 0; i < (size); ++i)
	{
		printf(" %d ," , ints[i]);
	}
	printf("\n");
	
	return 0;
}
