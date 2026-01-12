/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

__attribute__((always_inline)) inline float
	clampf(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

__attribute__((always_inline)) inline float
	maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

__attribute__((always_inline)) inline void
	normalize_yaw(float *angle)
{
	while (*angle >= C_PI)
		*angle -= 2.f * C_PI;
	while (*angle < -C_PI)
		*angle += 2.f * C_PI;
}
