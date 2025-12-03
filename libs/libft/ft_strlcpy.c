/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0;
	return (ft_strlen(src));
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strlcpy, {
	char src[] = "Hello, World!";
	char dest[255] = "                   ";
	ASSERT(ft_strlcpy(dest, src, 0) == ft_strlen(src));
	ASSERT(dest[0] == ' ');
	ASSERT(ft_strlcpy(dest, src, 1) == ft_strlen(src));
	ASSERT(dest[0] == 0);
	ASSERT(ft_strlcpy(dest, src, 2) == ft_strlen(src));
	ASSERT(dest[0] == 'H');
	ASSERT(dest[1] == 0);
})
*/
