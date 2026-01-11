/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

void
	game_interact(t_app *app)
{
	t_ray	ray;

	ray_init(&app->game.player, 0.f, &ray);
	ray_cast(app, &ray);
	if (ray.hit->type == MAT_DOOR && ray.perp_dist < 1)
	{
		action_text(app, "Press E to open");
		if (ui_key_pressed(app, KEY_E))
			map_state_door_interact(map_state_get(app, ray.map_x, ray.map_y),
				app);
	}
}
