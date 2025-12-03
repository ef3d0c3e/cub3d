/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:04:26 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	if (dest_len >= size)
		return (src_len + size);
	i = 0;
	while (src[i] && i + dest_len < size - 1)
	{
		dest[i + dest_len] = src[i];
		++i;
	}
	dest[i + dest_len] = 0;
	return (dest_len + src_len);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strlcat, {
	char src[] = "World!";
	char dest[255] = "Hello, ";
	ASSERT(ft_strlcat(dest, src, 0) == ft_strlen(src));
	ASSERT(ft_strlen(dest) + ft_strlen(src) == ft_strlcat(dest, src, 25));
})
*/
