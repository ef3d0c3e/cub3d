/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

int
	ft_strcmp(const char *a, const char *b)
{
	while (*a && *b == *a)
	{
		++a;
		++b;
	}
	return (*a - *b);
}

char
	*ft_strndup(const char *str, size_t n)
{
	char *const	buf = xmalloc(n + 1);

	ft_memcpy(buf, str, n);
	buf[n] = 0;
	return (buf);
}
