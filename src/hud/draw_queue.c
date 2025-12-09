/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Draw a single @ref t_draw_item */
static inline void
	draw_item(t_app *app, const t_draw_item *item)
{
	static void (*const	drawers[])(t_app *app, const t_draw_item *item) = {
	[DRAW_TEXT] = hud_draw_text,
	[DRAW_TEXT_SHADOW] = hud_draw_text_shadow,
	[DRAW_SPRITE] = hud_draw_sprite_item,
	};

	drawers[item->type](app, item);
}

t_draw_item
	*hud_draw(t_app *app, t_draw_item item)
{
	if (app->hud.queue.size == app->hud.queue.capacity)
	{
		app->hud.queue.capacity *= 2;
		app->hud.queue.items = xrealloc(app->hud.queue.items,
				sizeof(t_draw_item) * app->hud.queue.size,
				sizeof(t_draw_item) * app->hud.queue.capacity);
	}
	app->hud.queue.items[app->hud.queue.size] = item;
	return (&app->hud.queue.items[app->hud.queue.size++]);
}

void
	hud_render(t_app *app)
{
	size_t	i;

	i = 0;
	while (i < app->hud.queue.size)
	{
		draw_item(app, &app->hud.queue.items[i]);
		++i;
	}
	app->hud.queue.size = 0;
}
