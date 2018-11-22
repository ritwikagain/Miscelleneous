#include <bits/stdc++.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define META_SIZE sizeof(block_meta)

struct block_meta
{
	size_t size;
	struct block_meta* next;
	bool free;
};
block_meta * global_base = NULL;

block_meta * request_space (block_meta * last, size_t size)
{
	block_meta * block = (block_meta *)sbrk (0);
	block_meta * request = (block_meta *)sbrk (size + META_SIZE);
	if ((void *)request == (void *)-1)
	{
		return NULL;
	}
	assert (block == request);
	
	if (last)
	{
		last->next = block;
	}
	
	block->size = size;
	block->next = NULL;
	block->free = false;
	
	return block;
}
block_meta * find_free_block (block_meta ** last, size_t size)
{
	block_meta * current = *last;
	while (current && (current->free == false || current->size < size))
	{
		*last = current;
		current = current->next;
	}
	return current;
}
void * mymalloc (size_t size)
{
	if (size <= 0)
	{
		return NULL;
	}
	
	block_meta * block;
	if (global_base == NULL)
	{
		block = request_space (NULL, size);
		if (block == NULL)
		{
			return NULL;
		}
	}
	else
	{
		block_meta * last = global_base;
		block = find_free_block (&last, size);
		if (block == NULL)
		{
			block = request_space (last, size);
			if (block == NULL)
			{
				return NULL;
			}
		}
		else
		{
			block->free = false;
		}
	}
	return (block + 1);
}
int main ()
{
	int *n = (int *)mymalloc (sizeof(int));
	*n = 5;
	cout << *n << endl;
}