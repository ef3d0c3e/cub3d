/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

void
	*xmalloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		size = 1;
	ptr = malloc(size);
	if (!ptr)
		exit(1);
	return (ptr);
}

void
	*xrealloc(void *ptr, size_t oldsz, size_t newsz)
{
	void	*new;

	if (newsz == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (oldsz >= newsz)
		return (ptr);
	new = ft_memcpy(xmalloc(newsz), ptr, oldsz);
	free(ptr);
	return (new);
}
