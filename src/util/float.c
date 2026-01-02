/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

inline float
	clampf(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	return (value);
}

inline float
	maxf(float a, float b)
{
	if (a >= b)
		return (a);
	return (b);
}

inline void
	normalize_angle(float *angle, bool norm_pitch)
{
	if (norm_pitch)
	{
		*angle = clampf(*angle, -C_PI/2.f + 0.01f, C_PI/2.f - 0.01f);
	}
	else
	{
		while (*angle >= C_PI)
			*angle -= 2.f * C_PI;
		while (*angle < -C_PI)
			*angle += 2.f * C_PI;
	}
}
