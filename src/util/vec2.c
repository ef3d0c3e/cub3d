/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

float
	vec2_dist(t_vec2 x, t_vec2 y)
{
	const float	dx = x.x - y.x;
	const float	dy = x.y - y.y;

	return (sqrtf(dx * dx + dy * dy));
}

t_vec2
	vec2_dir(t_vec2 from, t_vec2 to)
{
	const float		dist = vec2_dist(from, to);

	return ((t_vec2){
		(to.x - from.x) / dist,
		(to.y - from.y) / dist,
	});
}

t_vec2
	vec2_scale(t_vec2 v, float x)
{
	return ((t_vec2){v.x * x, v.y * x});
}
