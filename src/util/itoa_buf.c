/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>
#include <limits.h>

static inline size_t
	base10_len(unsigned int x)
{
	size_t	len;

	len = 0;
	while (x)
	{
		++len;
		x /= 10;
	}
	return (len);
}

char
	*itoa_buf(char *buf, int x)
{
	size_t			pos;
	unsigned int	val;

	if (!x)
		return (ft_memcpy(buf, "0", 2));
	pos = 0;
	val = (unsigned int)x;
	if (x < 0)
	{
		buf[pos++] = '-';
		val = -(unsigned int)x;
	}
	pos += base10_len(val);
	buf[pos] = 0;
	while (val)
	{
		buf[--pos] = (char)((val % 10) + '0');
		val /= 10;
	}
	return (buf);
}

char
	*ftoa_buf(char *buf, float x, int prec)
{
	size_t			pos;
	unsigned int	val;
	size_t			len;

	if (x == 0)
		return (ft_memcpy(buf, "0", 2));
	pos = 0;
	if (x < 0)
		buf[pos++] = '-';
	itoa_buf(buf + pos, absi((int)x));
	val = (unsigned int)((x - floorf(x)) * pow(10, prec));
	len = ft_strlen(buf);
	pos += len + (size_t)prec + (x >= 0);
	ft_memset(buf + len + 1, '0', (size_t)prec);
	buf[len] = '.';
	buf[pos] = 0;
	while (val)
	{
		buf[--pos] = (char)((val % 10) + '0');
		val /= 10;
	}
	return (buf);
}
