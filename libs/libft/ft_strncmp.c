/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t				i;
	const unsigned char	*x;
	const unsigned char	*y;

	x = (const unsigned char *)a;
	y = (const unsigned char *)b;
	i = 0;
	while (i < n && x[i] && y[i] && x[i] == y[i])
		++i;
	return ((i != n) * (x[i] - y[i]));
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strncmp, {
	ASSERT(ft_strncmp("A", "AB", 20) == -66);
	ASSERT(ft_strncmp("A", "AB", 1) == 0);
	ASSERT(ft_strncmp("AB", "A", 2) == 66);
	ASSERT(ft_strncmp("AB", "A", 1) == 0);
	ASSERT(ft_strncmp("A", "A", 64) == 0);
	ASSERT(ft_strncmp("AC", "AB", 1) == 0);
	ASSERT(ft_strncmp("CC", "AB", 1) == 2);
})
*/
