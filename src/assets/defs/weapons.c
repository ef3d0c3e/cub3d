/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static bool
	loader_shotgun(t_app *app, t_assets *assets)
{
	t_weapon *const	weapon = &assets->weapons[WEAPON_SHOTGUN];

	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/player_shotgun.xpm", &weapon->view_model.texture);
	if (!weapon->view_model.texture)
		return (false);
	weapon->anim_shoot_time = .4f;
	weapon->view_model.background = 0x0FFFFF;
	weapon->view_model.off_left = 72;
	weapon->view_model.off_top = 1;
	weapon->view_model.sep_left = 0;
	weapon->view_model.sep_top = 1;
	weapon->view_model.width = 233;
	weapon->view_model.height = 162;
	weapon->item_model = (t_sprite){.texture = assets->items,
		.background = 0x0FFFFF,
		.line_size = assets->items->width,
		.left = 64, .top = 15,
		.width = 63, .height = 12};
	return (asset_size_check(weapon->view_model.texture, 306, 1582));
}

bool
	asset_loader_weapons(t_app *app, t_assets *assets)
{
	if (!loader_shotgun(app, assets))
		return (false);
	return (true);
}
