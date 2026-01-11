/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_entity_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

static inline float
	length(t_app *app)
{
	t_ray	ray;

	ray_init(&app->game.player, 0, &ray);
	ray_cast(app, &ray);
	return (ray.perp_dist);
}

bool
	ray_entities(t_app *app, t_proj_ent *found)
{
	struct s_render_ent_data	render;
	const float					depth = length(app);
	const t_proj_ent			*ent;
	size_t						i;

	project_entities(app, &render, "mob_");
	if (!render.num)
		return (false);
	i = render.num - 1;
	while (1)
	{
		ent = &render.ents[i];
		if (ent->dist < depth
			&& ent->start_x <= app->sizes.x / 2
			&& ent->end_x > app->sizes.x / 2)
		{
			*found = *ent;
			return (true);
		}
		if (!i)
			break ;
		--i;
	}
	return (false);
}
