/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_init(t_app *app)
{
	float	sx;
	float	sy;

	sx = (float)app->sizes.x / 1024.f * .5f;
	sy = (float)app->sizes.y / 1024.f * .5f;
	if (sx <= sy)
		app->hud.scale = sx;
	else
		app->hud.scale = sy;
	app->hud.queue.items = xmalloc(sizeof(t_draw_item) * 256);
	app->hud.queue.capacity = 256;
	pan_init(app, .5f, (int[2]){2, 2});
}

void
	hud_free(t_app *app)
{
	free(app->hud.queue.items);
}
