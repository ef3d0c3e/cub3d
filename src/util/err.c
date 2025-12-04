/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

static inline size_t
	hdr_size(void)
{
	static size_t hdr_size;

	if (!hdr_size)
	{
		hdr_size = sizeof(struct s_err_str_hdr);
		if (hdr_size % 16)
			hdr_size += 16 - (hdr_size % 16);
	}
	return (hdr_size);
}

struct s_err_str_hdr
	*err_hdr(t_err_str err)
{
	return ((struct s_err_str_hdr *)((char *)err - hdr_size()));
}

t_err_str
	err(t_err_str errstr, const char *str)
{
	struct s_err_str_hdr	*hdr = err_hdr(errstr);
	char					*buf;
	const size_t			len = ft_strlen(str);

	if (!errstr)
	{
		buf = xmalloc(hdr_size() + len + 1);
		*((struct s_err_str_hdr *)buf) = (struct s_err_str_hdr){len, len + 1,
			{0, 0, 0}};
		ft_memcpy(buf + hdr_size(), str, len + 1);
		return (buf + hdr_size());
	}
	while (hdr->capacity <= hdr->size + len + 1)
		hdr->capacity = hdr->capacity * 2 + !hdr->capacity * 16;
	buf = xmalloc(hdr_size() + hdr->capacity);
	*((struct s_err_str_hdr *)buf) = (struct s_err_str_hdr){hdr->size + len,
		hdr->capacity, hdr->style};
	ft_memcpy(buf + hdr_size(), errstr, hdr->size);
	ft_memcpy(buf + hdr_size() + hdr->size, str, len + 1);
	free(hdr);
	return (buf + hdr_size());

}

void
	err_free(t_err_str err)
{
	if (!err || !err[0])
		return ;
	free(err - hdr_size());
}
