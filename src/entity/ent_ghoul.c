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
	ent->health = 20;
	ent->hurt_time = 0.f;
	return (ent);
}

static void
	ghoul_tick(struct s_app *app, void *entity)
{
	struct s_ent_ghoul *const	ghoul = entity;

	if (ghoul->hurt_time != 0.f)
	{
		ghoul->hurt_time -= app->frame_delta;
		if (ghoul->hurt_time <= 0.f)
		{
			ghoul->hurt_time = 0.f;
			ghoul->base.data.color = 0xFFFFFF;
		}
	}
}

static void
	ghoul_interact(
	struct s_app *app,
	void *entity,
	struct s_ent_interaction interaction)
{
	struct s_ent_ghoul *const	ghoul = entity;

	if (interaction.kind == ENTI_ATTACK)
	{
		ghoul->health -= interaction.u_data.damage;
		ghoul->base.data.color = 0xFF4F4F;
		ghoul->hurt_time = 0.3f;
	}
	if (ghoul->health <= 0)
		rb_delete(&app->entities, ghoul);
}

t_entity_type
	*ent_type_ghoul(void)
{
	static t_entity_type	data = {
		.name = "ghoul",
		.load_fn = ghoul_load,
		.create_fn = ghoul_create,
		.tick_fn = ghoul_tick,
		.interact_fn = ghoul_interact,
		.hitbox_size = {.15f, .15f},
	};

	return (&data);
}
