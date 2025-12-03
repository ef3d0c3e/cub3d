/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:35:22 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:16:00 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t n)
{
	size_t	len;
	char	*ret;
	size_t	i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	len = ((len >= n) * n + (len < n) * len);
	if (len <= start)
		len = 0;
	ret = malloc(len + 1);
	if (!ret)
		return (ret);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i + start];
		++i;
	}
	ret[i] = 0;
	return (ret);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(substr, {
	char	*str = "Lorem ipsum dolor sit amet";

	ASSERT(ft_strncmp(ft_substr(str, 0, 255), str, 255) == 0);
	ASSERT(ft_strncmp(ft_substr(str, 5, 10), str + 5, 10) == 0);
	ASSERT(ft_strncmp(ft_substr(str, 15, 1), str + 15, 1) == 0);
})
*/
