/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	log10i(int x)
{
	int	lg;

	if (x == 0)
		return (1);
	lg = 0;
	while (x != 0)
	{
		x /= 10;
		++lg;
	}
	return (lg);
}

char	*ft_itoa(int x)
{
	int		len;
	char	*ret;

	len = log10i(x);
	ret = malloc((x < 0) + len + 1);
	if (!ret)
		return (ret);
	if (x < 0)
		ret[0] = '-';
	ret[(x < 0) + len] = 0;
	while (len > 0)
	{
		ret[(x < 0) + len - 1] = (x % 10) * ((x >= 0) - (x < 0)) + '0';
		x /= 10;
		--len;
	}
	return (ret);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(itoa, {
	ASSERT(ft_strncmp(ft_itoa(123456), "123456", 255) == 0);
	ASSERT(ft_strncmp(ft_itoa(-123456), "-123456", 255) == 0);
	ASSERT(ft_strncmp(ft_itoa(0), "0", 255) == 0);
	ASSERT(ft_strncmp(ft_itoa(2147483647), "2147483647", 255) == 0);
	ASSERT(ft_strncmp(ft_itoa(-2147483648), "-2147483648", 255) == 0);
})
*/
