/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:59:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/06/24 10:24:15 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

static inline void
	qsort_loop(
	const struct s_qsort_param *p,
	char **tmp,
	char *b[2],
	size_t n[2])
{
	while (n[0] > 0 && n[1] > 0)
	{
		if (p->cmp(b[0], b[1]) <= 0)
		{
			*tmp = (char *)ft_memcpy(*tmp, b[0], p->s) + p->s;
			b[0] += p->s;
			--n[0];
		}
		else
		{
			*tmp = (char *)ft_memcpy(*tmp, b[1], p->s) + p->s;
			b[1] += p->s;
			--n[1];
		}
	}
}

static void
	qsort_impl(const struct s_qsort_param *p, void *base, size_t num)
{
	char	*tmp;
	char	*b[2];
	size_t	n[2];

	if (num <= 1)
		return ;
	n[0] = num / 2;
	n[1] = num - n[0];
	b[0] = base;
	b[1] = (char *)base + (n[0] * p->s);
	tmp = p->t;
	qsort_impl(p, b[0], n[0]);
	qsort_impl(p, b[1], n[1]);
	qsort_loop(p, &tmp, b, n);
	if (n[0] > 0)
		ft_memcpy (tmp, b[0], n[0] * p->s);
	ft_memcpy (base, p->t, (num - n[1]) * p->s);
}

void
	ft_qsort_base(void *base, size_t nmemb, struct s_qsort_param p)
{
	if (nmemb <= 1)
		return ;
	qsort_impl(&p, base, nmemb);
}

void
	ft_qsort(void *base, size_t nmemb, size_t size,
	int (*cmp)(const void *, const void *))
{
	size_t					total_size;
	char					*buf;
	struct s_qsort_param	qsort_param;

	if (nmemb <= 1)
		return ;
	total_size = nmemb * size;
	buf = xmalloc(total_size);
	qsort_param.s = size;
	qsort_param.cmp = cmp;
	qsort_param.t = buf;
	qsort_impl(&qsort_param, base, nmemb);
	free(buf);
}
