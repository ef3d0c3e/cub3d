/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_item_ammo_chaingun.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static bool
	item_load(t_app *app)
{
	t_entity_type *const	type = ent_type_item_ammo_chaingun();

	ft_memset(&type->model, 0, sizeof(type->model));
	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/items.xpm", &type->model.texture);
	if (!type->model.texture)
		return (false);
	type->model.background = (t_color)0x00FFFF;
	type->model.off_left = 11;
	type->model.off_top = 66;
	type->model.width = 28;
	type->model.height = 16;
	return (true);
}

static void
	*item_create(struct s_app *app, t_entity_data data, void *cookie)
{
	struct s_ent_item *const	ent = xmalloc(sizeof(struct s_ent_item));

	(void)app;
	(void)cookie;
	ent->base.type = ent_type_item_ammo_chaingun();
	ent->base.data = data;
	return (ent);
}

static void
	item_tick(struct s_app *app, void *entity)
{
	struct s_ent_item *const	item = entity;
	const t_weapon				*weapon = &app->assets.weapons[WEAPON_CHAINGUN];
	t_player_weapondata *const	data = &app->game.player.weapons
	[WEAPON_CHAINGUN];

	const float					dist = vec2_dist(item->base.data.position,
		app->game.player.position);

	if (dist < .4f && data->ammo < weapon->max_ammo)
	{
		data->ammo = clamp(data->ammo + 100, 0,
				app->assets.weapons[WEAPON_CHAINGUN].max_ammo);
		item->base.data.delete = true;
	}

}

static void
	item_interact(
	struct s_app *app,
	void *entity,
	struct s_ent_interaction interaction)
{
	(void)app;
	(void)entity;
	(void)interaction;
}

t_entity_type
	*ent_type_item_ammo_chaingun(void)
{
	static t_entity_type	data = {
		.name = "item_ammo_chaingun",
		.offset = {.31f, 450.f},
		.scale = {0.4f, 0.2f},
		.load_fn = item_load,
		.create_fn = item_create,
		.tick_fn = item_tick,
		.interact_fn = item_interact,
		.hitbox_size = {.15f, .15f},
	};

	return (&data);
}

