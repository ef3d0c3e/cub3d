/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static void
	debug_ent(t_app *app)
{
	static int				id;
	t_entity_type *const	ent = (t_entity_type *)
		ent_get_type((enum e_ent_id)id);
	static char				buf[256] = "Entity: ";
	t_vec2					pos;

	pan_text(" \x7f Entity Debug");
	ft_memcpy(buf + 8, ent->name, ft_strlen(ent->name) + 1);
	pan_push_columns("DEBUG_ENT", 2);
	pan_slider_i(buf, &id, (int [2]){0, ENT_NUM_ - 1});
	pan_slider_f("X Offset", &ent->offset.x, (float [2]){-1, 1});
	pan_slider_f("Y Offset", &ent->offset.y, (float [2]){-500, 500});
	pan_next_columns();
	if (pan_button("Spawn"))
	{
		pos = app->game.player.position;
		pos.x += app->game.player.dir.x * 2;
		pos.y += app->game.player.dir.y * 2;
		ent_spawn(app, (enum e_ent_id)id, (t_entity_data){
		{0, 0}, pos, {0, 0}, {0, 0}, {0, 0}, false, 0xFFFFFF, false
		});
	}
	pan_slider_f("X Scale", &ent->scale.x, (float [2]){0.05f, 1});
	pan_slider_f("Y Scale", &ent->scale.y, (float [2]){0.05f, 1});
	pan_pop_columns();
}

void
	game_debug(t_app *app)
{
	t_player *const	player = &app->game.player;
	static bool		show;

	if (app->game.infinite_ammo && app->game.player.weapon_id != WEAPON_NONE)
		app->game.player.weapons[app->game.player.weapon_id].ammo
			= app->assets.weapons[app->game.player.weapon_id].max_ammo;
	if (ui_key_pressed(app, KEY_F1))
		show = !show;
	if (!show)
		return ;
	app->event.mouse_grab = false;
	pan_push_columns("DEBUG", 3);
	if (pan_button("Ammo") && player->weapon_id != WEAPON_NONE)
		player->weapons[player->weapon_id].ammo
			= app->assets.weapons[player->weapon_id].max_ammo;
	if (pan_button("HP"))
		player->health = 100;
	pan_next_columns();
	pan_checkbox("Minimap", &app->game.show_minimap);
	pan_next_columns();
	pan_checkbox("Infinite Ammo", &app->game.infinite_ammo);
	pan_pop_columns();
	debug_ent(app);
}
