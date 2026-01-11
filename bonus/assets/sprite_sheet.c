/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sheet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <assets/assets.h>

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

int
	sprite_sheet_anim_count(const t_sprite_sheet *sheet)
{
	int	count;
	int	y;

	count = 0;
	y = sheet->off_top;
	while (1)
	{
		if (y != sheet->off_left)
			y += sheet->off_top;
		y += sheet->height;
		if (y >= sheet->texture->height)
			break ;
		++count;
	}
	return (count);
}
