/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/06 14:27:06 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	if (!s || !f)
		return ((char *)s);
	i = 0;
	ret = malloc(ft_strlen(s) + 1);
	if (!ret)
		return (ret);
	while (s[i])
	{
		ret[i] = f(i, s[i]);
		++i;
	}
	ret[i] = 0;
	return (ret);
}

/*
#include "test/test.h"

static char capitalize(unsigned int sz, char c)
{
	(void)sz;
	return ft_toupper(c);
}

FT_EXPORT_TEST(strmapi, {
	ASSERT(ft_strncmp(ft_strmapi("Hello, World!", capitalize),
	"HELLO, WORLD!", 255) == 0);
})

*/
