/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	pan_mouse_hovered(t_app *app, t_vec2 bb_min, t_vec2 bb_max)
{
	const t_pos	min = (t_pos){
		(int)(bb_min.x * (float)app->sizes.x),
		(int)(bb_min.y * (float)app->sizes.y),
	};
	const t_pos	max = (t_pos){
		(int)(bb_max.x * (float)app->sizes.x),
		(int)(bb_max.y * (float)app->sizes.y),
	};

	if (app->event.mouse_pos.x < min.x
		|| app->event.mouse_pos.x > max.x
		|| app->event.mouse_pos.y < min.y
		|| app->event.mouse_pos.y > max.y)
		return (false);
	return (true);
}
