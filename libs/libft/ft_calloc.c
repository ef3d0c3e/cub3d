/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:20:34 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 16:26:23 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t sz)
{
	size_t	i;
	char	*data;

	data = malloc(n * sz);
	if (data)
	{
		i = 0;
		while (i < n * sz)
			data[i++] = 0;
	}
	return (data);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(calloc, {
	int *v = ft_calloc(1, 4);
	ASSERT(*v == 0);
	free(v);

	char *data = ft_calloc(2, 128);
	ASSERT(data[255] == 0);
	free(data);
})
*/
