/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/04 11:54:01 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = 0;
	while (*s)
	{
		if (*s == c)
			ret = (char *)s;
		++s;
	}
	if (*s == c)
		return ((char *)s);
	return (ret);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(strrchr, {
	ASSERT(ft_strrchr("Hello, World!", 'l')[1] == 'o');
	ASSERT(ft_strrchr("ABAC", '\0')[0] == 0);
	ASSERT(ft_strrchr("ABAC", 'A')[1] == 'C');
})
*/
