/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <util/util.h>

__attribute__((always_inline)) inline t_color
	color_lerp8(t_color x, t_color y, uint8_t f)
{
	uint8_t	c[3];
	uint8_t	w;
	uint8_t	iw;

	w = f;
	iw = 255 - w;
	c[0] = (uint8_t)(((x & 0xFF) * iw + (y & 0xFF) * w) / 255);
	c[1] = (uint8_t)((((x >> 8) & 0xFF) * iw
				+ ((y >> 8) & 0xFF) * w) / 255);
	c[2] = (uint8_t)((((x >> 16) & 0xFF) * iw
				+ ((y >> 16) & 0xFF) * w) / 255);
	return ((t_color)c[0] | ((t_color)c[1] << 8) | ((t_color)c[2] << 16));
}

__attribute__((always_inline)) inline t_color
	color_lerp(t_color x, t_color y, float f)
{
	if (f <= 0.f)
		return (x);
	if (f >= 1.f)
		return (y);
	return (color_lerp8(x, y, (uint8_t)(f * 255.f + 0.5f)));
}

__attribute__((always_inline)) inline t_color
	color_tint(t_color x, t_color y)
{
	uint8_t	c[3];

	c[0] = (uint8_t)(((x & 0xFF) * (y & 0xFF) + 128) >> 8);
	c[1] = (uint8_t)((((x >> 8) & 0xFF) * ((y >> 8) & 0xFF) + 128) >> 8);
	c[2] = (uint8_t)((((x >> 16) & 0xFF) * ((y >> 16) & 0xFF) + 128) >> 8);
	return ((t_color)c[0] | ((t_color)c[1] << 8) | ((t_color)c[2] << 16));
}

__attribute__((always_inline)) inline t_color
	color_add(t_color x, t_color y)
{
	const uint8_t	r[2] = {x & 0xFF, y & 0xFF};
	const uint8_t	g[2] = {(x >> 8) & 0xFF, (y >> 8) & 0xFF};
	const uint8_t	b[2] = {(x >> 16) & 0xFF, (y >> 16) & 0xFF};

	return ((t_color)(clamp(r[0] + r[1], 0, 255)
		+ (clamp(g[0] + g[1], 0, 255) << 8)
		+ (clamp(b[0] + b[1], 0, 255) << 16)));
}
