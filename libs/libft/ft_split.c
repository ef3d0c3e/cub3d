/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:42:26 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:32:08 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		inword;

	words = 0;
	inword = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!inword)
				++words;
			inword = 1;
		}
		else
			inword = 0;
		++s;
	}
	return (words);
}

static ssize_t	next(const char *str, char c)
{
	ssize_t	n;

	n = 0;
	while (str[n])
	{
		if (c == str[n])
			return (n);
		++n;
	}
	return (-1);
}

static char	*ndup(const char *src, ssize_t n)
{
	char	*ret;
	size_t	i;
	size_t	len;

	if (n >= 0)
		len = n;
	else
	{
		len = 0;
		while (src[len])
			++len;
	}
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len && src[i])
	{
		ret[i] = src[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	ssize_t	n;
	size_t	i;
	size_t	p;

	if (!s)
		return ((char **)s);
	ret = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (ret);
	i = 0;
	n = 0;
	p = 0;
	n = next(s + p, c);
	while (n != -1)
	{
		if (n != 0)
			ret[i++] = ndup(s + p, n);
		p += n + 1;
		n = next(s + p, c);
	}
	if (s[p])
		ret[i++] = ndup(s + p, -1);
	ret[i] = 0;
	return (ret);
}

/*
#include "test/test.h"

#define CLEANUP(__X) { \
	for (int i = 0; (__X)[i]; ++i) \
	{ \
		free((__X)[i]); \
	} \
	free((__X)); \
}

FT_EXPORT_TEST(split, {
	char	**res;

	res = ft_split("A B", ' ');
	ASSERT(ft_strncmp(res[0], "A", 255) == 0);
	ASSERT(ft_strncmp(res[1], "B", 255) == 0);
	CLEANUP(res);

	res = ft_split("     A    ", ' ');
	ASSERT(ft_strncmp(res[0], "A", 255) == 0);
	CLEANUP(res);

	res = ft_split("A", ' ');
	ASSERT(ft_strncmp(res[0], "A", 255) == 0);
	CLEANUP(res);

	res = ft_split("A   ", ' ');
	ASSERT(ft_strncmp(res[0], "A", 255) == 0);
	CLEANUP(res);

	res = ft_split("   A", ' ');
	ASSERT(ft_strncmp(res[0], "A", 255) == 0);
	CLEANUP(res);

	res = ft_split("0.1.2.3.4.5.6.7.8.9", '.');
	ASSERT(ft_strncmp(res[0], "0", 255) == 0);
	ASSERT(ft_strncmp(res[1], "1", 255) == 0);
	ASSERT(ft_strncmp(res[2], "2", 255) == 0);
	ASSERT(ft_strncmp(res[3], "3", 255) == 0);
	ASSERT(ft_strncmp(res[4], "4", 255) == 0);
	ASSERT(ft_strncmp(res[5], "5", 255) == 0);
	ASSERT(ft_strncmp(res[6], "6", 255) == 0);
	ASSERT(ft_strncmp(res[7], "7", 255) == 0);
	ASSERT(ft_strncmp(res[8], "8", 255) == 0);
	ASSERT(ft_strncmp(res[9], "9", 255) == 0);
	CLEANUP(res);
})

#undef CLEANUP
*/
