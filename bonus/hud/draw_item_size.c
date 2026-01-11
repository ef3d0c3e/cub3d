/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_item_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static inline void
	draw_item_size1(const t_app *app, t_vec2 *size, const t_draw_item *item)
{
	const t_font	*font = NULL;

	if (item->type == DRAW_TEXT)
	{
		font = &item->draw.text.font;
		size->x = (float)font->base_size.x * font->scale.x / (float)app->sizes
			.x * (float)ft_strlen(item->draw.text.text) + item->draw.text.pos.x;
		size->y = (float)font->base_size.y * font->scale.y
			/ (float)app->sizes.y + item->draw.text.pos.y;
	}
	else if (item->type == DRAW_TEXT_SHADOW)
	{
		font = &item->draw.text_shadow.font;
		size->x = (float)font->base_size.x * font->scale.x / (float)app->sizes
			.x * (float)ft_strlen(item->draw.text_shadow.text)
			+ item->draw.text_shadow.pos.x;
		size->y = (float)font->base_size.y * font->scale.y
			/ (float)app->sizes.y + item->draw.text_shadow.pos.y;
	}
	else if (item->type == DRAW_SPRITE)
		*size = (t_vec2){item->draw.sprite.pos.x + item->draw.sprite.scale.x
			* (float)item->draw.sprite.sprite.width / (float)app->sizes.x,
			item->draw.sprite.pos.y + item->draw.sprite.scale.y
			* (float)item->draw.sprite.sprite.height / (float)app->sizes.y};
}

static inline void
	draw_item_size2(const t_app *app, t_vec2 *size, const t_draw_item *item)
{
	(void)app;
	if (item->type == DRAW_RECT)
	{
		size->x = item->draw.rect.pos.x + item->draw.rect.size.x;
		size->y = item->draw.rect.pos.y + item->draw.rect.size.y;
	}
	else if (item->type == DRAW_RECT_RADIUS)
	{
		size->x = item->draw.rect_radius.pos.x + item->draw.rect_radius.size.x;
		size->y = item->draw.rect_radius.pos.y + item->draw.rect_radius.size.y;
	}
}

t_vec2
	draw_item_size(const t_app *app, const t_draw_item *item)
{
	t_vec2	size;

	draw_item_size1(app, &size, item);
	draw_item_size2(app, &size, item);
	return (size);
}
