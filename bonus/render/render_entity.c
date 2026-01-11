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

__attribute__((always_inline)) __attribute__((hot)) __attribute__((flatten))
	inline void
	render_entity_pix(
	t_app *app,
	const t_proj_ent *s,
	int x,
	int y)
{
	const int		d_pix = (y - app->game.player.pitch
			- s->vmove_y) * 256 - app->sizes.y * 128 + s->h * 128;
	t_color			color;
	t_pos			t;

	t.y = d_pix * s->sprite.height / s->h / 256;
	if (t.y < 0 || t.y >= s->sprite.height)
		return ;
	t.x = (x - s->real_start_x) * s->sprite.width / s->w;
	if (s->flip)
		t.x = s->sprite.width - 1 - t.x;
	if (t.x < 0 || t.x >= s->sprite.width)
		return ;
	color = sprite_sample_tx(&s->sprite, t.x, t.y);
	if (color != (t_color)COLOR_UNINIT)
		((t_color *)app->framebuffer->data)[x + y * app->sizes.x]
			= color_tint(color, s->ent->data.color);
}

void
	render_entities(
	t_app *app)
{
	struct s_render_ent_data	render;
	const t_proj_ent			*ent;
	size_t						i;
	t_pos						t;

	project_entities(app, &render, NULL);
	i = 0;
	while (i < render.num)
	{
		ent = &render.ents[i];
		t.x = ent->start_x;
		while (t.x < ent->end_x)
		{
			if (t.x >= 0 && ent->dist < app->z_buffer[t.x])
			{
				t.y = ent->start_y;
				while (t.y < ent->end_y)
					render_entity_pix(app, ent, t.x, t.y++);
			}
			++t.x;
		}
		++i;
	}
}
