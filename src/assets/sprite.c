/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <assets/assets.h>

inline t_color
	sprite_sample(const t_sprite *spr, float u, float v)
{
	t_color	col;
	int		x;
	int		y;

	if (u >= 1.f)
		x = spr->left + (spr->width - 1);
	else if (u <= 0.f)
		x = spr->left;
	else
		x = spr->left + (int)((float)(spr->width - 1) * u);
	if (v >= 1.f)
		y = spr->top + (spr->height - 1);
	else if (v <= 0.f)
		y = spr->top;
	else
		y = spr->top + (int)((float)(spr->height - 1) * v);
	col = ((t_color *)spr->texture->img->data)[x + y * spr->line_size];
	if (col == spr->background)
		return ((t_color)COLOR_UNINIT);
	return (col);
}

inline t_color
	sprite_sample_bilinear(const t_sprite *spr, float u, float v)
{
	const t_color	*buf = (const t_color *)spr->texture->img->data;
	t_color			cols[4];
	t_vec2			texel;
	t_pos			tp[2];
	uint8_t			f[2];

	u = clampf(u, 0.f, 1.f);
	v = clampf(v, 0.f, 1.f);
	texel = (t_vec2){(float)spr->width * u - .5f, (float)spr->height * v - .5f};
	tp[0] = (t_pos){(int)texel.x, (int)texel.y};
	tp[1] = (t_pos){clamp(tp[0].x + 1, 0, spr->width - 1),
		clamp(tp[0].y + 1, 0, spr->height - 1)};
	f[0] = (uint8_t)((maxf(texel.x, 0.f) - (float)tp[0].x) * 255.f + 0.5f);
	f[1] = (uint8_t)((maxf(texel.y, 0.f) - (float)tp[0].y) * 255.f + 0.5f);
	cols[0] = buf[tp[0].x + spr->left + (tp[0].y + spr->top) * spr->line_size];
	cols[1] = buf[tp[1].x + spr->left + (tp[0].y + spr->top) * spr->line_size];
	cols[2] = buf[tp[0].x + spr->left + (tp[1].y + spr->top) * spr->line_size];
	cols[3] = buf[tp[1].x + spr->left + (tp[1].y + spr->top) * spr->line_size];
	cols[0] = color_lerp8(
			color_lerp8(cols[0], cols[1], f[0]),
			color_lerp8(cols[2], cols[3], f[0]),
			f[1]);
	if (cols[0] == spr->background)
		return ((t_color)COLOR_UNINIT);
	return (cols[0]);
}

inline t_sprite
	sprite_sheet_get(const t_sprite_sheet *sheet, int x, int y)
{
	t_sprite	spr;

	spr.texture = sheet->texture;
	spr.background = sheet->background;
	spr.width = sheet->width;
	spr.height = sheet->height;
	spr.left = sheet->off_left + sheet->sep_left * x + spr.width * x;
	spr.top = sheet->off_top + sheet->sep_top * y + spr.height * y;
	spr.line_size = sheet->texture->width;
	return (spr);
}

inline t_color
	sprite_sheet_sample(const t_sprite_sheet *sheet, t_pos id, t_vec2 uv)
{
	const t_sprite	spr = sprite_sheet_get(sheet, id.x, id.y);

	return (sprite_sample(&spr, uv.x, uv.y));
}
