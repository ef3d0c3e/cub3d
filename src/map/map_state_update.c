/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_state_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static void
	traverse(size_t depth, t_rbnode *node, void *arg)
{
	t_app *const	app = arg;

	(void)depth;
	(*(const t_map_state_base **)node->data)->update_fn(node->data, app);
}

void
	map_state_update(t_app *app)
{
	rb_apply(&app->map.map_state, traverse, app);
}
