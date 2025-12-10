/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_ghoul.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static bool
	ghoul_load(t_app *app)
{
	t_entity_type *const	type = ent_type_ghoul();

	atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
		"assets/ghoul.xpm", &type->model.texture);
	if (!type->model.texture)
		return (false);
	type->model.background = (t_color)0x00FFFF;
	type->model.width = 41;
	type->model.height = 40;
	type->model.off_left = 1;
	type->model.off_top = 16;
	type->model.sep_left = 1;
	type->model.sep_top = 1;
	return (asset_size_check(type->model.texture, 463, 301));
}

static void
	*ghoul_create(struct s_app *app, t_entity_data data, void *cookie)
{
	struct s_ent_ghoul *const	ent = xmalloc(sizeof(struct s_ent_ghoul));

	(void)app;
	(void)cookie;
	ent->base.type = ent_type_ghoul();
	ent->base.data = data;
	return (ent);
}

static void
	ghoul_tick(struct s_app *app, void *entity)
{
	struct s_ent_ghoul *const	ghoul = entity;

	(void)app;
	(void)ghoul;
}

t_entity_type
	*ent_type_ghoul(void)
{
	static t_entity_type	data = {
		.name = "ghoul",
		.load_fn = ghoul_load,
		.create_fn = ghoul_create,
		.tick_fn = ghoul_tick,
		.hitbox_size = {.15f, .15f},
	};

	return (&data);
}
