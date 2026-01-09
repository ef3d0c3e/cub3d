/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_chaingun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static inline void
	shoot(t_app *app)
{
	t_proj_ent	ent;

	app->game.player.velocity.x -= app->game.player.dir.x * 0.2f;
	app->game.player.velocity.y -= app->game.player.dir.y * 0.2f;
	if (!ray_entities(app, &ent))
		return ;
	ent.ent->type->interact_fn(app, ent.ent, (t_ent_interaction){
		.kind = ENTI_ATTACK,
		.u_data.s_attack = {
			.damage = 7,
			.knockback = 5,
		}
	});
}

static void
	use(t_app *app, const t_weapon *this, t_player_weapondata *data)
{
	static float	usetime;

	(void)this;
	data->anim.y = 0;
	if (!data->ammo)
	{
		usetime = 0.f;
		return ;
	}
	if (ui_mouse_held(app, MOUSE_LEFT))
	{
		usetime += app->frame_delta;
		data->anim.y = (int)(usetime * 4.f) % 2;
		if (usetime > 1.8f)
		{
			data->anim.y = 2 + ((int)(usetime * 10.f) % 2);
			if ((int)(usetime * 10.f) % 2 == 0)
			{
				data->ammo -= 1;
				shoot(app);
			}
		}
	}
	else
		usetime = 0.f;
}

static void
	draw(t_app *app, const t_weapon *this, t_player_weapondata *data)
{
	const float	scale = (float)app->sizes.x / 114.f * .45f;
	float		y;

	y = 1.f - (106.f * scale / 2.f) / (float)app->sizes.y;
	y = clampf(y, .5f + 106.f * scale / (float)app->sizes.y / 2.f, 1.f);
	hud_draw(app, (t_draw_item){
		.type = DRAW_SPRITE,
		.draw.sprite = {
		.sprite = sprite_sheet_get(&this->view_model,
			data->anim.x, data->anim.y),
		.color = 0xFFFFFF,
		.scale = (t_vec2){scale, scale},
		.pos = {.5f, y},
	}});
}

bool
	asset_loader_weapon_chaingun(t_app *app, t_assets *assets)
{
	t_weapon *const	weapon = &assets->weapons[WEAPON_CHAINGUN];

	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/player_chaingun.xpm", &weapon->view_model.texture);
	if (!weapon->view_model.texture)
		return (false);
	weapon->anim_shoot_time = .2f;
	weapon->max_ammo = 500;
	weapon->use = use;
	weapon->draw = draw;
	weapon->view_model.background = 0x00FFFF;
	weapon->view_model.off_left = 0;
	weapon->view_model.off_top = 0;
	weapon->view_model.sep_left = 0;
	weapon->view_model.sep_top = 0;
	weapon->view_model.width = 114;
	weapon->view_model.height = 106;
	return (asset_size_check(weapon->view_model.texture, 114, 424));
}
