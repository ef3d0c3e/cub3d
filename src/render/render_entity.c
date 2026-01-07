/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samberna <samberna@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/07/02 23:20:23 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static void
	render_entity(
	t_app *app,
	t_ray_ent *s,
	int x,
	int y)
{
	const int pitch = 0;
	const int		d_pix = (y - pitch) * 256
		- app->sizes.y * 128 + s->h * 128;
	t_color			color;
	t_pos			t;

	// TODO UV refactor
	t.y = d_pix * s->sprite.height / s->h / 256;
	if (t.y < 0 || t.y >= s->sprite.height)
		return ;
	t.x = s->sprite.left + (x - s->start_x) * s->sprite.width / s->w;
	if (s->flip)
		t.x = s->sprite.left + s->sprite.width - 1 - (t.x - s->sprite.left);
	if (t.x < s->sprite.left || t.x >= s->sprite.left + s->sprite.width)
		return ;
	color = sprite_sample(&s->sprite, (float)t.x / (float)s->sprite.width, (float)t.y / (float)s->sprite.height);
	if (color != (t_color)COLOR_UNINIT)
		((t_color *)app->framebuffer->data)[x + y * app->sizes.x] = color;
}


void
	render_entities(
	t_app *app)
{
	struct s_render_ent_data	render;
	const t_ray_ent				*ent;
	size_t						i;

	ray_cast_entities(app, &render);
	i = 0;
	while (i < render.num)
	{
		ent = &render.ents[i];
		for (int x = ent->start_x; x < ent->end_x; ++x)
		{
			if (x < 0 || x >= app->sizes.x || ent->dist >= app->z_buffer[x])
				continue ;

			for (int y = 0; y < app->sizes.y; ++y)
			{
				render_entity(app, ent, x, y);
			}
		}
		++i;
	}
}
