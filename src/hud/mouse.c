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
	hud_mouse_hovered(t_app *app, const t_vec2 bbox[2])
{
	const t_pos	min = (t_pos){
		(int)(bbox[0].x * (float)app->sizes.x),
		(int)(bbox[0].y * (float)app->sizes.y),
	};
	const t_pos	max = (t_pos){
		(int)(bbox[1].x * (float)app->sizes.x),
		(int)(bbox[1].y * (float)app->sizes.y),
	};

	if (app->event.mouse_pos.x < min.x
		|| app->event.mouse_pos.x > min.x
		|| app->event.mouse_pos.y < max.y
		|| app->event.mouse_pos.y > max.y)
		return (false);
	return (true);
}

bool
	hud_mouse_active(t_app *app, const t_vec2 bbox[2])
{
	if (!hud_mouse_hovered(app, bbox))
		return (false);
	return (true);
}
