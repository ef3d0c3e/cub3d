/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;

	if (!dest && !src)
		return (dest);
	i = 0;
	if (src < dest)
	{
		while (i < n)
		{
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
			++i;
		}
	}
	else
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			++i;
		}
	}
	return (dest);
}

/*
#include "test/test.h"
#include <string.h>

FT_EXPORT_TEST(memmove, {
	char src[255] = "Hello, World!";
	char *dest = src + 1;
	ft_memmove(dest, src, 14);
	ASSERT(dest[0] == 'H');
	ASSERT(dest[1] == 'e');
	ASSERT(dest[12] == '!');
	ASSERT(dest[13] == 0);
})
*/
