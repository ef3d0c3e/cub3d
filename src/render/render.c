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

/** @brief Floor/Ceiling color fragment shader */
static __attribute__((always_inline)) inline void
	render_fc(t_app *app, const struct s_render_fc_data *r)
{
	const float			dist = vec2_dist2(app->game.player.position, r->world);
	t_color				color;

	color = *(t_color *)(r->tex->img->data + r->t.y * r->tex->img->size_line
			+ r->t.x * (r->tex->img->bpp / 8));
	color = color_lerp8(color, 0x000000, (uint8_t)(r->props->reflectivity
				/ (1 + r->ray->perp_dist / 2)));
	color = color_lerp8(color, 0x000000, (uint8_t)((255 - r->props->emission)
				/ (1 + dist / 2)));
	((t_color *)app->framebuffer->image->data)[r->s.x + r->s.y * app->sizes.x]
		= color;
}

static __attribute__((always_inline)) inline void
	render_ceiling(t_app *app, int x, int start_y, const t_ray *r)
{
	int						p;
	const t_material		*mat;
	struct s_render_fc_data	render;

	render.ray = r;
	render.s.x = x;
	render.s.y = 0;
	while (render.s.y < start_y)
	{
		p = app->sizes.y / 2 - render.s.y++;
		if (p <= 0)
			continue ;
		render.world.x = app->game.player.position.x
			+ (float)app->sizes.y / (float)(2 * p) *r->ray.x;
		render.world.y = app->game.player.position.y
			+ (float)app->sizes.y / (float)(2 * p) *r->ray.y;
		mat = map_get(app, (int)render.world.x, (int)render.world.y);
		render.tex = atlas_tex_get(&app->texture_atlas, mat->tex_ids[0]);
		render.props = &mat->props[0];
		render.t.x = (int)((render.world.x - (float)(int)render.world.x)
				* (float)render.tex->width);
		render.t.y = (int)((render.world.y - (float)(int)render.world.y)
				* (float)render.tex->height);
		render_fc(app, &render);
	}
}

static __attribute__((always_inline)) inline void
	render_floor(t_app *app, int x, int end_y, const t_ray *r)
{
	int						p;
	const t_material		*mat;
	struct s_render_fc_data	render;

	render.ray = r;
	render.s.x = x;
	render.s.y = end_y + 1;
	while (render.s.y < app->sizes.y)
	{
		p = render.s.y++ - app->sizes.y / 2;
		if (p <= 0)
			continue ;
		render.world.x = app->game.player.position.x
			+ (float)app->sizes.y / (float)(2 * p) *r->ray.x;
		render.world.y = app->game.player.position.y
			+ (float)app->sizes.y / (float)(2 * p) *r->ray.y;
		mat = map_get(app, (int)render.world.x, (int)render.world.y);
		render.tex = atlas_tex_get(&app->texture_atlas, mat->tex_ids[1]);
		render.props = &mat->props[1];
		render.t.x = (int)((render.world.x - (float)(int)render.world.x)
				* (float)render.tex->width);
		render.t.y = (int)((render.world.y - (float)(int)render.world.y)
				* (float)render.tex->height);
		render_fc(app, &render);
	}
}

static __attribute__((always_inline)) inline void
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
	while (x < app->sizes.x)
	{
		ray_init(&app->game.player,
			2.f * ((float)x / (float)app->sizes.x) - 1.f, &r);
		ray_cast(app, &r);
		app->z_buffer[x] = r.perp_dist;
		render_slice(app, x, &r);
		++x;
	}
	render_entities(app);
}
