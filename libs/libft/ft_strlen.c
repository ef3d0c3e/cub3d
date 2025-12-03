/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strlen, {
	ASSERT(ft_strlen("") == 0);
	ASSERT(ft_strlen("A") == 1);
	ASSERT(ft_strlen("AB") == 2);
	ASSERT(ft_strlen("ABC") == 3);
	ASSERT(ft_strlen("ABCD") == 4);
	ASSERT(ft_strlen("ABCDE") == 5);
	ASSERT(ft_strlen("ABCDEF") == 6);
	ASSERT(ft_strlen("ABCDEFG") == 7);
	ASSERT(ft_strlen("ABCDEFGH") == 8);
	ASSERT(ft_strlen("ABCDEFGHI") == 9);
})
*/
