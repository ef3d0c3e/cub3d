/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:48 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:07:29 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ret;
	size_t	i;

	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (ret)
	{
		i = 0;
		while (i <= len)
		{
			ret[i] = s[i];
			++i;
		}
	}
	return (ret);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strdup, {
	ASSERT(ft_strdup("AB")[1] == 'B');
	ASSERT(ft_strdup("")[0] == '\0');
	ASSERT(ft_strdup("A")[0] == 'A');
	ASSERT(ft_strdup("A")[1] == '\0');
})
*/
