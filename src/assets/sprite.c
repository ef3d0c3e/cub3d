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

	if (u > 1.f)
		x = spr->left + (spr->width - 1);
	else if (u < 0.f)
		x = spr->left;
	else
		x = spr->left + (int)((float)(spr->width - 1) * u);
	if (v > 1.f)
		y = spr->top + (spr->height - 1);
	else if (v < 0.f)
		y = spr->top;
	else
		y = spr->top + (int)((float)(spr->height - 1) * v);
	col = ((t_color *)spr->texture->img->data)[x + y * spr->line_size];
	if (col == spr->background)
		return ((t_color)COLOR_UNINIT);
	return (col);
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
