/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_memcmp(const void *a, const void *b, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && ((const unsigned char *)a)[i]
			== ((const unsigned char *)b)[i])
	{
		++i;
	}
	return (((const unsigned char *)a)[i] - ((const unsigned char *)b)[i]);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(memcmp, {
	ASSERT(ft_memcmp("A", "AB", 2) == -66);
	ASSERT(ft_memcmp("A", "AB", 1) == 0);
	ASSERT(ft_memcmp("A", "B", 0) == 0);
	ASSERT(ft_memcmp("AB", "A", 2) == 66);
	ASSERT(ft_memcmp("AB", "A", 1) == 0);
	ASSERT(ft_memcmp("A", "A", 1) == 0);
	ASSERT(ft_memcmp("AC", "AB", 1) == 0);
	ASSERT(ft_memcmp("CC", "AB", 1) == 2);
	ASSERT(ft_memcmp("A\0a", "A\0b", 3) == -1);
})
*/
