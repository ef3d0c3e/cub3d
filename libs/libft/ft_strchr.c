/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return (0);
		++s;
	}
	return ((char *)s);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strchr, {
	ASSERT(ft_strchr("Hello, World!", 'W')[0] == 'W');
	ASSERT(ft_strchr("ABC", '\0')[0] == 0);
	ASSERT(ft_strchr("ABC", 'U') == 0);
})
*/
