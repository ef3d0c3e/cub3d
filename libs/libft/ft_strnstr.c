/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:07:06 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	find_len;
	size_t	match;
	size_t	i;

	if (n == 0)
		return ((char *)haystack);
	if (!*needle)
		return ((char *)haystack);
	find_len = ft_strlen(needle);
	match = 0;
	i = 0;
	while (haystack[i] && i < n)
	{
		if (haystack[i] == needle[match])
			++match;
		else
			match = 0;
		if (match == find_len)
			return ((char *)haystack + i - find_len + 1);
		++i;
	}
	return (0);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strnstr, {
	ASSERT(ft_strnstr("Lorem ipsum", "ips", 9)[0] == 'i');
	ASSERT(ft_strnstr("Lorem ipsum", "ips", 8) == NULL);
	ASSERT(ft_strnstr("Lorem ipsum", "dolor", 11) == NULL);
	ASSERT(ft_strnstr("Lorem ipsum", "", 11)[0] == 'L');
	ASSERT(ft_strnstr("", "Lorem", 0) == NULL);
})
*/
