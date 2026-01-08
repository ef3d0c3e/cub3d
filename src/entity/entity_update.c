/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Apply `tick_fn` on all entities in the RBTree */
static void
	traverse(size_t depth, t_rbnode *node, void *arg)
{
	t_app *const	app = arg;
	t_entity *const	ent = node->key;

	(void)depth;
	ent->type->tick_fn(app, ent);
}

void
	ent_update(t_app *app)
{
	rb_apply(&app->entities, traverse, app);
}
