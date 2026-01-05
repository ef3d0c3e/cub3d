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
	t_player *const	p = &app->game.player;

	p->fov = .66f;
	p->health = 100;
	p->angle.x = ((float)app->map.player_orientation / 2.f) * C_PI;
	normalize_angle(&p->angle.x, false);
	p->position = (t_vec2){
		(float)app->map.player_spawn.x + .5f,
		(float)app->map.player_spawn.y + .5f,
	};
	p->dir = (t_vec2){sinf(p->angle.x), cosf(p->angle.x)};
	p->plane = (t_vec2){p->dir.y * p->fov, p->dir.x * p->fov};
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
	app->game.player.angle.x += (ui_key_held(app, KEY_ARROW_RIGHT) - ui_key_held(app, KEY_ARROW_LEFT)) * .05f;
	if (app->event.mouse_grab)
		app->game.player.angle.x += (float)app->event.mouse_delta.x * 0.005f;
	player_move(app, move);
}
