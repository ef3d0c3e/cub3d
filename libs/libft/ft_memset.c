/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)dest)[i++] = (char)c;
	return (dest);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(memset, {
	char buffer[255];
	ft_memset(buffer, 0, 255);
	ft_memset(buffer, '*', 64);
	ASSERT(buffer[0] == '*');
	ASSERT(buffer[63] == '*');
	ASSERT(buffer[64] == 0);
})
*/
