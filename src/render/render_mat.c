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

void
	render_wall_init(
	t_app *app,
	const t_ray *r,
	struct s_render_wall_data *s)
{
	s->pix = (t_color *)app->framebuffer->image->data;
	s->line_h = (int)((float)app->sizes.y / r->perp_dist);
	if (s->line_h > app->sizes.y * 4)
		s->line_h = app->sizes.y * 4;
	s->ds = (int)(-(float)s->line_h / 2.f + (float)app->sizes.y / 2.f + app->game.player.angle.y);
	if (s->ds < 0)
		s->ds = 0;
	s->de = (int)((float)s->line_h / 2.f + (float)app->sizes.y / 2.f + app->game.player.angle.y);
	if (s->de >= app->sizes.y)
		s->de = app->sizes.y - 1;
	if (r->side == 0 && r->ray.x < 0)
		s->tex_id = ORI_WEST;
	else if (r->side == 0)
		s->tex_id = ORI_EAST;
	else if (r->ray.y < 0)
		s->tex_id = ORI_NORTH;
	else
		s->tex_id = ORI_SOUTH;
	s->tex = atlas_tex_get(&app->texture_atlas, r->hit->tex_ids[s->tex_id]);
	s->tw = s->tex->width;
	s->th = s->tex->height;
	if (r->side == 0)
		s->wall_x = app->game.player.position.y + r->perp_dist * r->ray.y;
	else
		s->wall_x = app->game.player.position.x + r->perp_dist * r->ray.x;
}

void
	render_wall(t_app *app, int x, const t_ray *r)
{
	struct s_render_wall_data	s;
	int							y;
	int							d;

	render_wall_init(app, r, &s);
	s.wall_x -= floor(s.wall_x);
	s.tx = s.wall_x * s.tw;
	if ((r->side == 0 && r->ray.x < 0) || (r->side == 1 && r->ray.y > 0))
		s.tx = s.tw - s.tx - 1;
	y = s.ds;
	while (y <= s.de)
	{
		d = (y - app->game.player.angle.y) * 256 - app->sizes.y * 128 + s.line_h * 128;
		s.ty = ((d * s.th) / s.line_h) / 256;
		if (s.ty < 0)
			s.ty = 0;
		else if (s.ty >= s.th)
			s.ty = s.th - 1;
		s.pix[x + y * (int)app->sizes.x] = *(uint32_t *)(s.tex->img->data
				+ s.ty * s.tex->img->size_line
				+ s.tx * (s.tex->img->bpp / 8));
		++y;
	}
}
