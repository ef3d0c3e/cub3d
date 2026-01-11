/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_state_door_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

static void
	update(void *this, t_app *app)
{
	struct s_map_state_door *const	door = this;

	if (door->direction == -1)
	{
		door->open = clampf(door->open - 0.05f, 0.f, 1.f);
		if (door->open == 0.f)
		{
			door->direction = 0;
			door->close_time = SIZE_MAX;
		}
	}
	else if (door->direction == 1)
	{
		door->open = clampf(door->open + 0.05f, 0.f, 1.f);
		if (door->open == 1.f)
			door->direction = 0;
	}
	if (door->open == 1.f && app->frame > door->close_time)
	{
		door->direction = -1;
	}
}

static const t_map_state_base
	*door_state(void)
{
	static const t_map_state_base	base = {
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
	state->close_time = SIZE_MAX;
	return (state);
}

void
	map_state_door_interact(void *this, t_app *app)
{
	struct s_map_state_door *const	door = this;

	if (door->direction == 0)
	{
		if (door->open == 0.f)
		{
			door->direction = 1;
			door->close_time = app->frame
				+ (size_t)(2.f / app->map.props.frame_time);
		}
	}
}
