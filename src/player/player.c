/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	player_setup(t_app *app)
{
	app->player.health = 100;
	app->player.angle.x = ((float)app->map.player_orientation / 2.f - 1.f)
		* (float)M_PI;
}

void
	player_move(t_app *app, t_vec2 move)
{

}


void
	player_input(t_app *app)
{
	t_vec2	move;

	move = (t_vec2){0, 0};
	if (ui_key_held(app, KEY_W))
		move.x += 1.f;
	if (ui_key_held(app, KEY_S))
		move.x += -1.f;
	if (ui_key_held(app, KEY_D))
		move.y += 1.f;
	if (ui_key_held(app, KEY_A))
		move.y += -1.f;
	player_move(app, move);
}
