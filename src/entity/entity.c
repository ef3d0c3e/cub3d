/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

const t_entity_type
	*ent_get_type(enum e_ent_id id)
{
	static t_entity_type *(*const	getters[])(void) = {
	[ENT_ITEM] = ent_type_item,
	[ENT_GHOUL] = ent_type_ghoul,
	};

	return (getters[id]());
}

bool
	ent_load_assets(t_app *app, t_assets *assets)
{
	enum e_ent_id	id;

	(void)assets;
	id = 0;
	while (id < ENT_NUM_)
	{
		if (!ent_get_type(id)->load_fn(app))
			return (false);
		++id;
	}
	return (true);
}

static int
	ent_cmp(const void *a, const void *b)
{
	const uintptr_t	lhs = (uintptr_t)a;
	const uintptr_t	rhs = (uintptr_t)b;

	if (lhs < rhs)
		return (-1);
	else if (lhs > rhs)
		return (1);
	return (0);
}

void
	ent_setup(struct s_app *app)
{
	app->entities = rb_new(ent_cmp, free, NULL);
}

void
	*ent_spawn(struct s_app *app, enum e_ent_id id, t_entity_data data)
{
	const t_entity_type	*type = ent_get_type(id);
	void				*ent;

	ent = type->create_fn(app, data, NULL);
	rb_insert(&app->entities, ent, NULL);
	return (ent);
}
