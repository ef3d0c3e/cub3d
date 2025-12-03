/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:50:57 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:17:24 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ret;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = malloc(len1 + len2 + 1);
	if (!ret)
		return (ret);
	i = 0;
	while (i < len1)
	{
		ret[i] = s1[i];
		++i;
	}
	while (i < len1 + len2)
	{
		ret[i] = s2[i - len1];
		++i;
	}
	ret[i] = 0;
	return (ret);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strjoin, {
		ASSERT(ft_strncmp(ft_strjoin("Hello,", " World!"),
		"Hello, World!", 255) == 0)
		ASSERT(ft_strncmp(ft_strjoin("", ""), "", 255) == 0)
		ASSERT(ft_strncmp(ft_strjoin("A", ""), "A", 255) == 0)
		ASSERT(ft_strncmp(ft_strjoin("", "A"), "A", 255) == 0)
})
*/
