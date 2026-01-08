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
	ent->health = 100;
	ent->hurt_time = 0.f;
	ent->aggro_time = 0.f;
	return (ent);
}

static void
	ghoul_tick(struct s_app *app, void *entity)
{
	struct s_ent_ghoul *const	ghoul = entity;
	const t_vec2				dir = vec2_dir(ghoul->base.data.position,
			app->game.player.position);
	const float					vel = 4.f + 10 * (ghoul->aggro_time > 0.f);

	if (vec2_dist(ghoul->base.data.position, app->game.player.position) < 10
		|| ghoul->aggro_time != 0.f)
	{
		ghoul->base.data.acceleration.x += dir.x * vel;
		ghoul->base.data.acceleration.y += dir.y * vel;
	}
	if (ghoul->hurt_time != 0.f)
	{
		ghoul->hurt_time -= app->frame_delta;
		if (ghoul->hurt_time <= 0.f)
		{
			ghoul->hurt_time = 0.f;
			ghoul->base.data.color = 0xFFFFFF;
		}
	}
	ghoul->aggro_time = clampf(ghoul->aggro_time - app->frame_delta, 0, 1e10);
		ghoul->base.data.anim_state.x = 0;
	if (ghoul->aggro_time != 0.f)
		ghoul->base.data.anim_state.x = 1 + ((int)(ghoul->aggro_time * 4) % 2);
}

static void
	ghoul_interact(
	struct s_app *app,
	void *entity,
	struct s_ent_interaction interaction)
{
	struct s_ent_ghoul *const	ghoul = entity;
	t_vec2						accel;

	if (interaction.kind == ENTI_ATTACK)
	{
		ghoul->health -= interaction.u_data.s_attack.damage;
		accel = vec2_scale(vec2_dir(app->game.player.position,
					ghoul->base.data.position),
				interaction.u_data.s_attack.knockback);
		ghoul->base.data.acceleration.x += accel.x * 10;
		ghoul->base.data.acceleration.y += accel.y * 10;
		ghoul->base.data.color = 0xFF4F4F;
		ghoul->hurt_time = 0.3f;
		ghoul->aggro_time = 7.f;
		ghoul->base.data.anim_state.x += 1;
	}
	if (ghoul->health <= 0)
		ghoul->base.data.delete = true;
}

t_entity_type
	*ent_type_ghoul(void)
{
	static t_entity_type	data = {
		.name = "ghoul",
		.offset = {0, 0},
		.scale = {1.f, 1.f},
		.load_fn = ghoul_load,
		.create_fn = ghoul_create,
		.tick_fn = ghoul_tick,
		.interact_fn = ghoul_interact,
		.hitbox_size = {.5f, .5f},
	};

	return (&data);
}
