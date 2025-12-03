/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)dest)[i++] = 0;
	return (dest);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(bzero, {
	char buffer[255];
	ft_bzero(buffer, 255);
	ASSERT(buffer[0] == 0);
	ASSERT(buffer[64] == 0);
	ASSERT(buffer[254] == 0);
})
*/
