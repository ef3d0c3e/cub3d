/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_item_heal_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

static bool
	item_load(t_app *app)
{
	t_entity_type *const	type = ent_type_item_heal();

	ft_memset(&type->model, 0, sizeof(type->model));
	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/items.xpm", &type->model.texture);
	if (!type->model.texture)
		return (false);
	type->model.background = (t_color)0x00FFFF;
	type->model.off_left = 174;
	type->model.off_top = 110;
	type->model.width = 28;
	type->model.height = 19;
	return (asset_size_check(type->model.texture, 597, 229));
}

static void
	*item_create(struct s_app *app, t_entity_data data, void *cookie)
{
	struct s_ent_item *const	ent = xmalloc(sizeof(struct s_ent_item));

	(void)app;
	(void)cookie;
	ent->base.type = ent_type_item_heal();
	ent->base.data = data;
	return (ent);
}

static void
	item_tick(struct s_app *app, void *entity)
{
	struct s_ent_item *const	item = entity;
	const float					dist = vec2_dist(item->base.data.position,
			app->game.player.position);

	if (dist < .4f && app->game.player.health != 100)
	{
		app->game.player.health = clamp(app->game.player.health + 30, 0, 100);
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
	*ent_type_item_heal(void)
{
	static t_entity_type	data = {
		.name = "item_heal",
		.offset = {.32f, 440.f},
		.scale = {0.4f, 0.23f},
		.load_fn = item_load,
		.create_fn = item_create,
		.tick_fn = item_tick,
		.interact_fn = item_interact,
		.hitbox_size = {.15f, .15f},
	};

	return (&data);
}
