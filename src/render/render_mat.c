/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static __attribute__((always_inline)) inline const t_texture
	*get_texture(const t_app *app, const t_ray *r)
{
	t_atlas_id	id;

	if (r->side == 0 && r->ray.x < 0)
		id = ORI_WEST;
	else if (r->side == 0)
		id = ORI_EAST;
	else if (r->ray.y < 0)
		id = ORI_NORTH;
	else
		id = ORI_SOUTH;
	if (r->hit->type == MAT_DOOR && id == ORI_NORTH)
		id += 2;
	else if (r->hit->type == MAT_DOOR && id == ORI_SOUTH)
		id += 1;
	if (r->hit->orientation != ORI_NONE)
	{
		id -= 1;
		id += ((t_atlas_id)r->hit->orientation - 1);
		id %= 4;
	}
	return (atlas_tex_get(&app->texture_atlas, r->hit->tex_ids[id]));
}

static __attribute__((always_inline)) inline void
	render_wall_init(
	t_app *app,
	const t_ray *r,
	struct s_render_wall_data *s)
{
	t_vec2	normal;

	s->pix = (t_color *)app->framebuffer->image->data;
	s->line_h = (int)((float)app->sizes.y / r->perp_dist);
	if (s->line_h > app->sizes.y * 4)
		s->line_h = app->sizes.y * 4;
	s->ds = (int)(-(float)s->line_h / 2.f + (float)app->sizes.y / 2.f
			+ app->game.player.angle.y);
	if (s->ds < 0)
		s->ds = 0;
	s->de = (int)((float)s->line_h / 2.f + (float)app->sizes.y / 2.f
			+ app->game.player.angle.y);
	if (s->de >= app->sizes.y)
		s->de = app->sizes.y - 1;
	s->tex = get_texture(app, r);
	if (r->side == 0)
		s->wall_x = app->game.player.position.y + r->perp_dist * r->ray.y;
	else
		s->wall_x = app->game.player.position.x + r->perp_dist * r->ray.x;
	if (r->side == 0)
		normal = (t_vec2){0.f, 1 - 2 * (r->ray.y >= 0)};
	else
		normal = (t_vec2){1 - 2 * (r->ray.x >= 0), 0.f};
	s->shade = clampf(vec2_dot(normal, vec2_scale(r->ray,
					-1.f / vec2_dist(r->ray, (t_vec2){0, 0}))), 0.f, 1.f);
}

static __attribute__((always_inline)) inline t_color
	sample(struct s_render_wall_data *s)
{
	t_color	color;

	color = *(t_color *)(s->tex->img->data + s->ty * s->tex->img->size_line
			+ s->tx * (s->tex->img->bpp / 8));
	return (color_lerp(color, 0x000000, s->shade / 2));
}

void
	render_wall(t_app *app, int x, const t_ray *r)
{
	struct s_render_wall_data	s;
	int							y;
	int							d;

	render_wall_init(app, r, &s);
	s.wall_x -= floorf(s.wall_x);
	s.tx = (int)(s.wall_x * (float)s.tex->width);
	if ((r->side == 0 && r->ray.x < 0) || (r->side == 1 && r->ray.y > 0))
		s.tx = s.tex->width - s.tx - 1;
	y = s.ds;
	while (y <= s.de)
	{
		d = (int)(((float)y - app->game.player.angle.y) * 256)
			- app->sizes.y * 128 + s.line_h * 128;
		s.ty = ((d * s.tex->height) / s.line_h) / 256;
		if (s.ty < 0)
			s.ty = 0;
		else if (s.ty >= s.tex->height)
			s.ty = s.tex->height - 1;
		s.pix[x + y * (int)app->sizes.x] = sample(&s);
		++y;
	}
}
