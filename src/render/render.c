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
	render_ceiling(t_app *app, int x, int start_y, t_ray *r)
{
	int				y;
	int				p;
	t_vec2			world;
	t_pos			t;
	const t_texture	*tex;

	y = 0;
	while (y < start_y)
	{
		p = app->sizes.y / 2 - y++;
		if (p <= 0)
			continue ;
		world.x = app->game.player.position.x
			+ ((.5f * (float)app->sizes.y) / (float)p) * r->ray.x;
		world.y = app->game.player.position.y
			+ ((.5f * (float)app->sizes.y) / (float)p) * r->ray.y;
		tex = atlas_tex_get(&app->texture_atlas, map_get(app,
					(int)world.x, (int)world.y)->tex_ids[0]);
		t.x = (int)((world.x - floorf(world.x)) * (float)tex->width);
		t.y = (int)((world.y - floorf(world.y)) * (float)tex->height);
		((t_color *)app->framebuffer->image->data)[x + y * app->sizes.x]
			= *(t_color *)(tex->img->data + t.y * tex->img->size_line
				+ t.x * (tex->img->bpp / 8));
	}
}

static void
	render_floor(t_app *app, int x, int end_y, t_ray *r)
{
	int				y;
	int				p;
	t_vec2			world;
	t_pos			t;
	const t_texture	*tex;

	y = end_y + 1;
	while (y < app->sizes.y)
	{
		p = y++ - app->sizes.y / 2;
		if (p <= 0)
			continue ;
		world.x = app->game.player.position.x
			+ ((.5f * (float)app->sizes.y) / (float)p) * r->ray.x;
		world.y = app->game.player.position.y
			+ ((.5f * (float)app->sizes.y) / (float)p) * r->ray.y;
		tex = atlas_tex_get(&app->texture_atlas, map_get(app,
					(int)world.x, (int)world.y)->tex_ids[1]);
		t.x = (int)((world.x - floorf(world.x)) * (float)tex->width);
		t.y = (int)((world.y - floorf(world.y)) * (float)tex->height);
		((t_color *)app->framebuffer->image->data)[x + y * app->sizes.x]
			= *(t_color *)(tex->img->data + t.y * tex->img->size_line
				+ t.x * (tex->img->bpp / 8));
	}
}

void
	render_slice(t_app *app, int x, const t_ray *r)
{
	int		line_h;
	int		ds;
	int		de;

	line_h = (int)((float)app->sizes.y / r->perp_dist);
	if (line_h > app->sizes.y * 4)
		line_h = app->sizes.y * 4;
	ds = (int)(-(float)line_h / 2.f + (float)app->sizes.y / 2.f
			+ app->game.player.angle.y);
	if (ds < 0)
		ds = 0;
	de = (int)((float)line_h / 2.f + (float)app->sizes.y / 2.f
			+ app->game.player.angle.y);
	if (de >= app->sizes.y)
		de = app->sizes.y - 1;
	render_ceiling(app, x, ds, r);
	render_wall(app, x, r);
	render_floor(app, x, de, r);
}

void
	render_frame(t_app *app)
{
	t_ray	r;
	int		x;

	x = 0;
	//while (x <  app->sizes.x)
#pragma omp parallel for private(x, r) shared(app) schedule(dynamic)
	for (x = 0; x < app->sizes.x; ++x)
	{
		ray_init(&app->game.player,
				2.f * ((float)x / (float)app->sizes.x) - 1.f, &r);
		ray_cast(app, &r);
		app->z_buffer[x] = r.perp_dist;
		render_slice(app, x, &r);
		//++x;
	}
	render_entities(app);
}
