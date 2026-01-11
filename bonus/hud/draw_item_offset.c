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

void
	vec_add(t_vec2 *a, t_vec2 b)
{
	a->x += b.x;
	a->y += b.y;
}

inline t_draw_item
	draw_item_offset(const t_app *app, t_draw_item item, t_vec2 offset)
{
	(void)app;
	if (item.type == DRAW_TEXT)
		vec_add(&item.draw.text.pos, offset);
	else if (item.type == DRAW_TEXT_SHADOW)
		vec_add(&item.draw.text_shadow.pos, offset);
	else if (item.type == DRAW_SPRITE)
		vec_add(&item.draw.sprite.pos, offset);
	else if (item.type == DRAW_RECT)
		vec_add(&item.draw.rect.pos, offset);
	else if (item.type == DRAW_RECT_RADIUS)
		vec_add(&item.draw.rect_radius.pos, offset);
	return (item);
}
