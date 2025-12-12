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

void
	game_debug(t_app *app)
{
	t_player *const	player = &app->game.player;
	static bool		show;

	if (ui_key_pressed(app, KEY_F1))
		show = !show;
	if (!show)
		return ;

	pan_push_columns("DEBUG", 3);
	if (pan_button("Ammo") && player->weapon_id != WEAPON_NONE)
		player->weapons[player->weapon_id].ammo
			= app->assets.weapons[player->weapon_id].max_ammo;
	if (pan_button("HP"))
		player->health = 100;
	if (pan_button("Armor"))
		player->armor = 100;
	pan_next_columns();
	pan_next_columns();
	pan_pop_columns();
}
