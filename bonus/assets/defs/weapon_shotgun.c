/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_shotgun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static inline void
	particle(t_app *app, t_vec2 dir, float dist)
{
	const float		ddir = vec2_dist(dir, (t_vec2){0, 0});
	const t_vec2	world = {
		app->game.player.position.x + dir.x * dist / ddir,
		app->game.player.position.y + dir.y * dist / ddir,
	};

	ent_spawn(app, ENT_PART_SHOTGUN, (t_entity_data){
		.acceleration = {0, 0},
		.angles = {0, 0},
		.anim_state = {0, 0},
		.color = 0x7f7f7f,
		.flip = false,
		.position = world,
		.velocity = {0, 0},
		.delete = false,
	});
}

static inline void
	shoot(t_app *app)
{
	t_proj_ent	ent;
	t_ray		r;

	app->game.player.velocity.x -= app->game.player.dir.x * 1.2f;
	app->game.player.velocity.y -= app->game.player.dir.y * 1.2f;
	if (!ray_entities(app, &ent))
	{
		ray_init(&app->game.player, 0.f, &r);
		ray_cast(app, &r);
		particle(app, r.ray, r.perp_dist);
		return ;
	}
	particle(app, (t_vec2){ent.ent->data.position.x
		- app->game.player.position.x, ent.ent->data.position.y
		- app->game.player.position.y}, ent.dist);
	ent.ent->type->interact_fn(app, ent.ent, (t_ent_interaction){
		.kind = ENTI_ATTACK,
		.u_data.s_attack = {
			.damage = 40,
			.knockback = 35,
		}
	});
}

static void
	use(t_app *app, const t_weapon *this, t_player_weapondata *data)
{
	const float		max_time = .7f;
	static float	usetime;

	(void)this;
	data->anim.y = 0;
	if (usetime != 0)
	{
		usetime = clampf(usetime - app->frame_delta, 0.f, 1e10f);
		data->anim.y = 1 + clamp((int)(7.f * (1.f - usetime / max_time)), 0, 6);
		return ;
	}
	if (!data->ammo)
		return ;
	if (ui_mouse_pressed(app, MOUSE_LEFT))
	{
		usetime = max_time;
		data->anim.y = 1;
		data->ammo -= 1;
		shoot(app);
	}
}

static void
	draw(t_app *app, const t_weapon *this, t_player_weapondata *data)
{
	const float	scale = (float)app->sizes.x / 233.f * .65f;
	float		y;

	y = 1.f - (162.f * scale / 2.f) / (float)app->sizes.y;
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
	asset_loader_weapon_shotgun(t_app *app, t_assets *assets)
{
	t_weapon *const	weapon = &assets->weapons[WEAPON_SHOTGUN];

	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/player_shotgun.xpm", &weapon->view_model.texture);
	if (!weapon->view_model.texture)
		return (false);
	weapon->anim_shoot_time = .8f;
	weapon->max_ammo = 96;
	weapon->use = use;
	weapon->draw = draw;
	weapon->view_model.background = 0x0FFFFF;
	weapon->view_model.off_left = 0;
	weapon->view_model.off_top = 0;
	weapon->view_model.sep_left = 0;
	weapon->view_model.sep_top = 0;
	weapon->view_model.width = 233;
	weapon->view_model.height = 162;
	return (asset_size_check(weapon->view_model.texture, 233, 1296));
}
