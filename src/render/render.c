/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static void
	render_ceiling(t_app *app, int x, int start)
{
	int	y;

	y = 0;
	while (y < start)
	{
		((t_color *)app->framebuffer->image->data)[x + y * app->sizes.x]
			= app->map.colors[1];
		++y;
	}
}

static void
	render_floor(t_app *app, int x, int end)
{
	int	y;

	y = end + 1;
	while (y < app->sizes.y)
	{
		((t_color *)app->framebuffer->image->data)[x + y * app->sizes.x]
			= app->map.colors[0];
		++y;
	}
}

void
	render_slice(t_app *app, int x, const t_ray *r)
{
	size_t	idx;
	int		line_h;
	int		ds;
	int		de;

	line_h = (int)((float)app->sizes.y / r->perp_dist);
	if (line_h > app->sizes.y * 4)
		line_h = app->sizes.y * 4;
	ds = (int)(-(float)line_h / 2.f + (float)app->sizes.y / 2.f + app->game.player.angle.y);
	if (ds < 0)
		ds = 0;
	de = (int)((float)line_h / 2.f + (float)app->sizes.y / 2.f + app->game.player.angle.y);
	if (de >= app->sizes.y)
		de = app->sizes.y - 1;
	render_ceiling(app, x, ds);
	render_wall(app, x, r);
	render_floor(app, x, de);
}

void
	render_frame(t_app *app)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x <  app->sizes.x)
	{
		ray_init(&app->game.player, 2.f * ((float)x / (float)app->sizes.x) - 1.f, &r);
		ray_cast(app, &r);
		app->z_buffer[x] = r.perp_dist;
		render_slice(app, x, &r);
		++x;
	}
	render_entities(app);
}
