/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2024/11/05 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	return (c == '\f'
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\r'
		|| c == ' ');
}

int	ft_atoi(const char *s)
{
	int	sign;
	int	value;

	while (ft_isspace(*s))
		++s;
	sign = 1;
	if (*s == '+')
		++s;
	else if (*s == '-')
	{
		sign = -1;
		++s;
	}
	value = 0;
	while (*s >= '0' && *s <= '9')
	{
		value = value * 10 + (*s - '0');
		++s;
	}
	return (value * sign);
}

/*
#include "test/test.h"

FT_EXPORT_TEST(atoi, {
	ASSERT(ft_atoi("123456") == 123456);
	ASSERT(ft_atoi("+123456") == 123456);
	ASSERT(ft_atoi("-123456") == -123456);
	ASSERT(ft_atoi("  123456") == 123456);
	ASSERT(ft_atoi(" \t\n\v\r +123456") == 123456);
	ASSERT(ft_atoi("\t-123456") == -123456);
	ASSERT(ft_atoi("a") == 0);
	ASSERT(ft_atoi("") == 0);
	ASSERT(ft_atoi("0") == 0);
	ASSERT(ft_atoi("+0") == 0);
	ASSERT(ft_atoi("-0") == 0);
})
*/
