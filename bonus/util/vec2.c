/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

__attribute__((always_inline)) inline float
	vec2_dist(t_vec2 a, t_vec2 b)
{
	const float	dx = a.x - b.x;
	const float	dy = a.y - b.y;

	return (sqrtf(dx * dx + dy * dy));
}

__attribute__((always_inline)) inline float
	vec2_dist2(t_vec2 a, t_vec2 b)
{
	const float	dx = a.x - b.x;
	const float	dy = a.y - b.y;

	return (dx * dx + dy * dy);
}

__attribute__((always_inline)) inline t_vec2
	vec2_dir(t_vec2 from, t_vec2 to)
{
	const float		dist = vec2_dist(from, to);

	return ((t_vec2){
		(to.x - from.x) / dist,
		(to.y - from.y) / dist,
	});
}

__attribute__((always_inline)) inline t_vec2
	vec2_scale(t_vec2 v, float x)
{
	return ((t_vec2){v.x * x, v.y * x});
}

__attribute__((always_inline)) inline float
	vec2_dot(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}
