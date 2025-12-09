/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_item_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

inline t_draw_item
	draw_item_offset(const t_app *app, t_draw_item item, t_vec2 offset)
{
	(void)app;
	if (item.type == DRAW_TEXT)
	{
		item.draw.text.pos.x += offset.x;
		item.draw.text.pos.y += offset.y;
	}
	else if (item.type == DRAW_TEXT_SHADOW)
	{
		item.draw.text_shadow.pos.x += offset.x;
		item.draw.text_shadow.pos.y += offset.y;
	}
	else if (item.type == DRAW_SPRITE)
	{
		item.draw.sprite.pos.x += offset.x;
		item.draw.sprite.pos.y += offset.y;
	}
	else if (item.type == DRAW_RECT)
	{
		item.draw.rect.pos.x += offset.x;
		item.draw.rect.pos.y += offset.y;
	}
	else if (item.type == DRAW_RECT_RADIUS)
	{
		item.draw.rect_radius.pos.x += offset.x;
		item.draw.rect_radius.pos.y += offset.y;
	}
	return (item);
}
