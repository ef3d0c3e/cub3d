/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((char *)s)[i] == c)
			return ((char *)s + i);
		++i;
	}
	return (0);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(memchr, {
	ASSERT(((char*)ft_memchr("Hello, World!", 'W', 14))[0] == 'W');
	ASSERT(((char*)ft_memchr("ABC", '\0', 4))[0] == 0);
	ASSERT(((char*)ft_memchr("\0ABC~", '~', 6))[0] == '~');
	ASSERT(ft_memchr("AAAAA", 'U', 5) == 0);
})
*/
