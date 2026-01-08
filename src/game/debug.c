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
	debug_ent(void)
{
	static int				id;
	t_entity_type *const	ent = (t_entity_type *)ent_get_type((enum e_ent_id)id);
	static char				buf[256] = "Entity: ";

	pan_text(" \x7f Entity Debug");
	ft_memcpy(buf + 8, ent->name, ft_strlen(ent->name) + 1);
	pan_slider_i(buf, &id, (int[2]){0, ENT_NUM_ - 1});
	pan_push_columns("DEBUG_ENT", 2);
	pan_slider_f("X Offset", &ent->offset.x, (float[2]){-1, 1});
	pan_slider_f("Y Offset", &ent->offset.y, (float[2]){-500, 500});
	pan_next_columns();
	pan_slider_f("X Scale", &ent->scale.x, (float[2]){0.05f, 1});
	pan_slider_f("Y Scale", &ent->scale.y, (float[2]){0.05f, 1});
	pan_pop_columns();
}

void
	game_debug(t_app *app)
{
	t_player *const	player = &app->game.player;
	static bool		show;

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
	if (pan_button("Armor"))
		player->armor = 100;
	pan_next_columns();
	static int score;
	pan_slider_i("Score", &score, (const int[2]){0, 999999});
	pan_next_columns();
	pan_pop_columns();
	debug_ent();
}
