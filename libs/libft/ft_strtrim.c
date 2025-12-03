/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:57:48 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:26:02 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ret;
	size_t	i;

	if (!set || !s1)
		return ((char *)s1);
	i = 0;
	while (*s1 && ft_strchr(set, *s1))
		++s1;
	len = ft_strlen(s1);
	while (len && ft_strchr(set, *(s1 + len - 1)))
		--len;
	ret = malloc(len + 1);
	if (!ret)
		return (ret);
	while (i < len)
	{
		ret[i] = s1[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}
/*
#include "test/test.h"

FT_EXPORT_TEST(strtrim, {
	ASSERT(ft_strncmp(ft_strtrim("\t\tHello\n\t", "\t\n "), "Hello", 255) == 0)
	ASSERT(ft_strncmp(ft_strtrim("\t\tHello \t\n World\t! ", "\t\n"),
	"Hello \t\n World\t!", 255) == 0)
})
*/
