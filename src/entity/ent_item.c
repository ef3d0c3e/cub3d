/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

// TODO..
static bool
	item_load(t_app *app)
{
	t_entity_type *const	type = ent_type_item();

	//atlas_tex_load(app->mlx_ptr, &app->texture_atlas,
	//	"assets/items.xpm", &type->model.texture);
	//if (!type->model.texture)
	//	return (false);
	//type->model.background = (t_color)0x000000;
	return (true);
}

static void
	*item_create(struct s_app *app, t_entity_data data, void *cookie)
{
	struct s_ent_item *const	ent = xmalloc(sizeof(struct s_ent_item));

	(void)app;
	(void)cookie;
	ent->base.type = ent_type_item();
	ent->base.data = data;
	return (ent);
}

static void
	item_tick(struct s_app *app, void *entity)
{
	struct s_ent_item *const	item = entity;

	(void)app;
	(void)item;
}

t_entity_type
	*ent_type_item(void)
{
	static t_entity_type	data = {
		.load_fn = item_load,
		.create_fn = item_create,
		.tick_fn = item_tick,
		.hitbox_size = (t_vec2){.15f, .15f},
	};

	return (&data);
}
