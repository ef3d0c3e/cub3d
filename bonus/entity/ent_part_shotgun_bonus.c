/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_part_shotgun_bonus.c                           :+:      :+:    :+:   */
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
	t_entity_type *const	type = ent_type_part_shotgun();

	ft_memset(&type->model, 0, sizeof(type->model));
	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/explosion.xpm", &type->model.texture);
	if (!type->model.texture)
		return (false);
	type->model.background = (t_color)0x00FFFF;
	type->model.width = 103;
	type->model.height = 86;
	type->model.off_left = 0;
	type->model.off_top = 0;
	type->model.sep_left = 0;
	type->model.sep_top = 0;
	return (asset_size_check(type->model.texture, 103, 258));
}

static void
	*item_create(struct s_app *app, t_entity_data data, void *cookie)
{
	struct s_ent_particle *const	ent
		= xmalloc(sizeof(struct s_ent_particle));

	(void)app;
	(void)cookie;
	ent->base.type = ent_type_part_shotgun();
	ent->base.data = data;
	ent->lifetime = 0;
	return (ent);
}

static void
	item_tick(struct s_app *app, void *entity)
{
	struct s_ent_particle *const	part = entity;

	part->lifetime += app->frame_delta;
	if (part->lifetime > 0.1)
		part->base.data.anim_state.y = 1;
	if (part->lifetime > 0.2)
		part->base.data.anim_state.y = 2;
	if (part->lifetime > 0.3)
		part->base.data.delete = true;
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
	*ent_type_part_shotgun(void)
{
	static t_entity_type	data = {
		.name = "part_shotgun",
		.offset = {.31f, 0.f},
		.scale = {0.4f, 0.4f},
		.load_fn = item_load,
		.create_fn = item_create,
		.tick_fn = item_tick,
		.interact_fn = item_interact,
		.hitbox_size = {.15f, .15f},
	};

	return (&data);
}
