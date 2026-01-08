/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_state_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static void
	update(void *this, t_app *app)
{
	struct s_map_state_door *const	door = this;

	(void)app;
	if (door->direction == -1)
	{
		door->open = clampf(door->open - 0.05f, 0.f, 1.f);
		if (door->open == 0)
			door->direction = 0;
	}
	else if (door->direction == 1)
	{
		door->open = clampf(door->open + 0.05f, 0.f, 1.f);
		if (door->open == 1)
			door->direction = 0;
	}
	if (door->direction == 0 && ui_key_released(app, KEY_O))
	{
		if (door->open == 0.f)
			door->direction = 1;
		else
			door->direction = -1;
	}
}

static const t_map_state_base
	*door_state(void)
{
	const static t_map_state_base	base = {
		.update_fn = update,
	};

	return (&base);
}

void
	*map_state_door(void)
{
	struct s_map_state_door	*state;

	state = xmalloc(sizeof(struct s_map_state_door));
	state->base = door_state();
	state->open = 0.f;
	state->direction = 0;
	return (state);
}
