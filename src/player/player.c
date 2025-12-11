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
	app->game.player.health = 100;
	app->game.player.angle.x = ((float)app->map.player_orientation / 2.f - 1.f)
		* (float)M_PI;
}

void
	player_move(t_app *app, t_vec2 move)
{
	(void)app;
	(void)move;
	// TODO
}


void
	player_input(t_app *app)
{
	t_player *const	player = &app->game.player;
	const t_weapon	*weapon = &app->assets.weapons[player->weapon];
	t_vec2	move;

	move = (t_vec2){
		ui_key_held(app, KEY_W) - ui_key_held(app, KEY_S),
		ui_key_held(app, KEY_D) - ui_key_held(app, KEY_A)
	};
	if (ui_key_released(app, KEY_U) && player->weapon_anim == 0)
	{
		player->weapon_anim = weapon->anim_shoot_time;
	}
	if (player->weapon_anim != 0)
	{
		player->weapon_anim -= app->frame_delta;
		player->weapon_anim = maxf(player->weapon_anim, 0);
	}
	player_move(app, move);
}
