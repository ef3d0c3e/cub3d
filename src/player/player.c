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
	const float fov = .5f;

	app->game.player.health = 100;
	app->game.player.angle.x = ((float)app->map.player_orientation / 2.f - 1.f)
		* (float)M_PI;
	app->game.player.position = (t_vec2){
		(float)app->map.player_spawn.x + .5f,
		(float)app->map.player_spawn.y + .5f,
	};

	app->game.player.dir = (t_vec2){sinf(app->game.player.angle.x), -cosf(app->game.player.angle.x)};
	app->game.player.plane = (t_vec2){cosf(app->game.player.angle.x) * fov, sinf(app->game.player.angle.x) * fov};
}

static t_vec2
	player_forward(const t_player *p, t_vec2 move)
{
	const float norm = sqrtf(powf(move.x, 2) + powf(move.y, 2));

	if (norm == 0)
		return ((t_vec2){0, 0});
	const float move_x_norm = -move.y / norm;
	const float move_y_norm = -move.x / norm;
	return (t_vec2){
		move_x_norm * cosf(p->angle.x) - move_y_norm * sinf(p->angle.x),
		move_x_norm * sinf(p->angle.x) + move_y_norm * cosf(p->angle.x)
	};
}

void
	player_move(t_app *app, t_vec2 move)
{
	const t_vec2	fwd = player_forward(&app->game.player, move);
	app->game.player.position.x -= .1f * fwd.x;
	app->game.player.position.y += .1f * fwd.y;
	app->game.player.angle.x += (ui_key_held(app, KEY_ARROW_RIGHT) - ui_key_held(app, KEY_ARROW_LEFT)) * .05f;

	const float fov = .5f;
	app->game.player.dir = (t_vec2){sinf(app->game.player.angle.x), -cosf(app->game.player.angle.x)};
	app->game.player.plane = (t_vec2){cosf(app->game.player.angle.x) * fov, sinf(app->game.player.angle.x) * fov};
	// TODO
}


void
	player_input(t_app *app)
{
	t_player *const	player = &app->game.player;
	const t_weapon	*weapon = &app->assets.weapons[player->weapon_id];
	t_vec2	move;

	move = (t_vec2){
		ui_key_held(app, KEY_W) - ui_key_held(app, KEY_S),
		ui_key_held(app, KEY_D) - ui_key_held(app, KEY_A)
	};
	if (player->weapon_id != WEAPON_NONE && ui_key_released(app, KEY_U)
		&& player->weapon_anim == 0 && player->weapons[player->weapon_id].ammo)
	{
		player->weapon_anim = weapon->anim_shoot_time;
		--player->weapons[player->weapon_id].ammo;
	}
	if (player->weapon_anim != 0)
	{
		player->weapon_anim -= app->frame_delta;
		player->weapon_anim = maxf(player->weapon_anim, 0);
	}
	player_move(app, move);
}
