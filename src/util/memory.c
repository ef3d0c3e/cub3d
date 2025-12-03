#include <util/util.h>

void
	*xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		size = 1;
	ptr = malloc(size);
	if (!ptr)
	{
		asm("int $3");
		exit(1);
	}
	return (ptr);
}

void
	*xrealloc(void *ptr, size_t oldsz, size_t newsz)
{
	void	*new;

	if (oldsz >= newsz)
		return (ptr);
	new = ft_memcpy(xmalloc(newsz), ptr, oldsz);
	free(ptr);
	return (new);
}
