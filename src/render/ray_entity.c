/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_entity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	ray_entities(t_app *app, t_proj_ent *found)
{
	struct s_render_ent_data	render;
	const t_proj_ent			*ent;
	size_t						i;

	project_entities(app, &render, "item");
	if (!render.num)
		return false;
	i = render.num - 1;
	while (1)
	{
		ent = &render.ents[i];
		if (ent->dist < app->z_buffer[app->sizes.x / 2]
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
