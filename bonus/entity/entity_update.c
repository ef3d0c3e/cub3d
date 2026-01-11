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

/**
 * @brief Make the entity move with a given motion
 *
 * @param app Application pointer
 * @param entity Entity to move
 * @param move Motion
 */
static void
	ent_move(t_app *app, t_entity *entity, t_vec2 move)
{
	const float	width = entity->type->hitbox_size.x;
	t_ray		ray;

	entity->data.angles = (t_vec2){atan2f(move.x, move.y), 0};
	if (move.x != 0.f)
	{
		ray_init_vec(entity->data.position, (t_vec2){move.x / fabsf(move.x), 0},
			&ray);
		ray_cast(app, &ray);
		move.x *= (ray.perp_dist >= fabsf(move.x) + width);
	}
	if (move.y != 0.f)
	{
		ray_init_vec(entity->data.position, (t_vec2){0, move.y / fabsf(move.y)},
			&ray);
		ray_cast(app, &ray);
		move.y *= (ray.perp_dist >= fabsf(move.y) + width);
	}
	entity->data.position.x += move.x;
	entity->data.position.y += move.y;
}

/** @brief Apply `tick_fn` on all entities in the RBTree */
static void
	traverse(size_t depth, t_rbnode *node, void *arg)
{
	t_app *const	app = arg;
	t_entity *const	ent = node->key;

	(void)depth;
	ent->type->tick_fn(app, ent);
	if (ent->data.delete)
	{
		rb_delete(&app->entities, ent);
		return ;
	}
	ent->data.velocity.x *= app->map.props.friction;
	ent->data.velocity.y *= app->map.props.friction;
	ent->data.velocity.x += ent->data.acceleration.x * app->frame_delta;
	ent->data.velocity.y += ent->data.acceleration.y * app->frame_delta;
	ent_move(app, ent, (t_vec2){ent->data.velocity.x * app->frame_delta,
		ent->data.velocity.y * app->frame_delta});
	ent->data.acceleration = (t_vec2){0, 0};
}

void
	ent_update(t_app *app)
{
	rb_apply(&app->entities, traverse, app);
}
