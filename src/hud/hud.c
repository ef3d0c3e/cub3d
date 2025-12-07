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
}

void
	hud_draw(t_app *app)
{
	const t_vec2	size = hud_textsize(app, "a");
	char	buf[1024];
	
	sprintf(buf, "(%f %f) (%f %f)", app->player.position.x, app->player.position.y, app->player.angle.x, app->player.angle.y);
	hud_texts(app, (t_pos){8, 8}, buf, .7f);
}
