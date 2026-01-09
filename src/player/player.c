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
	p->weapons[WEAPON_NONE].has_weapon = true;
	p->weapons[WEAPON_SHOTGUN].has_weapon = true;
	p->dir = (t_vec2){sinf(p->angle.x), cosf(p->angle.x)};
	p->plane = (t_vec2){p->dir.y * p->fov, p->dir.x * p->fov};
}

static void
	scroll_weapon(t_app *app, int direction)
{
	enum e_weapon_id	id;

	id = app->game.player.weapon_id;
	while (direction == -1)
	{
		if (id == WEAPON_NONE)
			id = WEAPON_NUM_;
		id -= 1;
		if (app->game.player.weapons[id].has_weapon)
			break ;
	}
	while (direction == 1)
	{
		id += 1;
		if (id == WEAPON_NUM_)
			id = WEAPON_NONE;
		if (app->game.player.weapons[id].has_weapon)
			break ;
	}
	app->game.player.weapon_id = id;
}

void
	player_input(t_app *app)
{
	t_player *const	player = &app->game.player;
	const t_weapon	*weapon = &app->assets.weapons[player->weapon_id];
	t_vec2			move;

	move = (t_vec2){
		ui_key_held(app, KEY_W) - ui_key_held(app, KEY_S),
		ui_key_held(app, KEY_D) - ui_key_held(app, KEY_A)
	};
	if (player->weapon_id != WEAPON_NONE)
		weapon->use(app, weapon, &app->game.player.weapons[player->weapon_id]);
	scroll_weapon(app, ui_mouse_released(app, MOUSE_WHEEL_DOWN)
		- ui_mouse_released(app, MOUSE_WHEEL_UP));
	app->game.player.angle.x += (ui_key_held(app, KEY_ARROW_RIGHT) - ui_key_held(app, KEY_ARROW_LEFT)) * .05f;
	if (app->event.mouse_grab)
		app->game.player.angle.x += (float)app->event.mouse_delta.x * 0.002f;
	app->game.player.pitch = (int)(256.f * sinf(app->game.player.angle.y));
	player_move(app, move);
}
