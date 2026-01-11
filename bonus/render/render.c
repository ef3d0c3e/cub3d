/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

/** @brief Floor/Ceiling color fragment shader */
__attribute__((always_inline)) __attribute__((hot)) __attribute__((flatten))
	inline void
	sample(t_app *app, const struct s_render_fc_data *r, t_pos bounds)
{
	const float			dist = vec2_dist2(app->game.player.position, r->world);
	t_color				color;
	t_color				cur;

	cur = r->props->reflect_color;
	if (r->s.y >= bounds.y && r->s.y < 2 * bounds.y - bounds.x)
		cur = ((t_color *)app->framebuffer->image->data)
		[r->s.x + (2 * bounds.y - r->s.y) * app->sizes.x];
	else if (r->s.y < bounds.x && r->s.y > 2 * bounds.x - bounds.y + 1)
		cur = ((t_color *)app->framebuffer->image->data)
		[r->s.x + (2 * bounds.x - r->s.y) * app->sizes.x];
	color = *(t_color *)(r->tex->img->data + r->t.y * r->tex->img->size_line
			+ r->t.x * (r->tex->img->bpp / 8));
	color = color_lerp8(color, cur, r->props->reflectivity);
	color = color_lerp8(color, r->props->fade_color,
			(uint8_t)((r->props->emission - 255) / (1 + dist / 64)));
	((t_color *)app->framebuffer->image->data)[r->s.x + r->s.y * app->sizes.x]
		= color;
}

__attribute__((always_inline)) __attribute__((hot)) __attribute__((flatten))
	inline void
	render_ceiling(t_app *app, int x, t_pos bounds, const t_ray *r)
{
	int						p;
	const t_material		*mat;
	struct s_render_fc_data	render;

	render.ray = r;
	render.s.x = x;
	render.s.y = 0;
	while (render.s.y < bounds.x)
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
		sample(app, &render, bounds);
	}
}

__attribute__((always_inline)) __attribute__((hot)) __attribute__((flatten))
	inline void
	render_floor(t_app *app, int x, t_pos bounds, const t_ray *r)
{
	int						p;
	const t_material		*mat;
	struct s_render_fc_data	render;

	render.ray = r;
	render.s.x = x;
	render.s.y = bounds.y + 1;
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
		sample(app, &render, bounds);
	}
}

__attribute__((always_inline)) __attribute__((hot)) __attribute__((flatten))
	inline void
	render_scanline(t_app *app, int x, const t_ray *r)
{
	int		line_h;
	int		ds;
	int		de;

	line_h = (int)((float)app->sizes.y / r->perp_dist);
	if (line_h > app->sizes.y * 4)
		line_h = app->sizes.y * 4;
	ds = (int)(-(float)line_h / 2.f + (float)app->sizes.y / 2.f
			+ (float)app->game.player.pitch);
	if (ds < 0)
		ds = 0;
	de = (int)((float)line_h / 2.f + (float)app->sizes.y / 2.f
			+ (float)app->game.player.pitch);
	if (de >= app->sizes.y)
		de = app->sizes.y - 1;
	render_wall(app, x, r);
	render_ceiling(app, x, (t_pos){ds, de}, r);
	render_floor(app, x, (t_pos){ds, de}, r);
}
