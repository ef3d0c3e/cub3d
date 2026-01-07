/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Move the player and check for collisions */
static void
	player_collide(t_app *app, float dt)
{
	t_player *const	p = &app->game.player;
	float			dx;
	float			dy;
	t_vec2			dir;
	t_ray			ray;

	dx = p->velocity.x * dt;
	if (dx != 0.0f)
	{
		dir = (t_vec2){(float)((dx > 0) - (dx <= 0)), 0.f};
		ray_init_vec(p->position, dir, &ray);
		ray_cast(app, &ray);
		p->velocity.x *= (ray.perp_dist >= fabsf(dx) + PLAYER_SIZE);
	}
	p->position.x += p->velocity.x * dt;
	dy = p->velocity.y * dt;
	if (dy != 0.0f)
	{
		dir = (t_vec2){0.f, (float)((dy > 0) - (dy <= 0))};
		ray_init_vec(p->position, dir, &ray);
		ray_cast(app, &ray);
		p->velocity.y *= (ray.perp_dist >= fabsf(dy) + PLAYER_SIZE);
	}
	p->position.y += p->velocity.y * dt;
}

/** @brief Compute the normalized player direction */
static t_vec2
	player_forward(const t_player *p, t_vec2 move)
{
	const float	norm = sqrtf(powf(move.x, 2) + powf(move.y, 2));
	float		move_norm[2];

	if (norm == 0)
		return ((t_vec2){0, 0});
	move_norm[0] = move.y / norm;
	move_norm[1] = move.x / norm;
	return ((t_vec2){
		move_norm[0] * cosf(p->angle.x) + move_norm[1] * sinf(p->angle.x),
		-move_norm[0] * sinf(p->angle.x) + move_norm[1] * cosf(p->angle.x)
	});
}

void
	player_move(t_app *app, t_vec2 move)
{
	const t_vec2		fwd = player_forward(&app->game.player, move);
	t_player *const		p = &app->game.player;
	t_map_props *const	pr = &app->map.props;

	p->velocity = (t_vec2){
		p->velocity.x * pr->friction + fwd.x * app->frame_delta * pr->accelerate,
		p->velocity.y * pr->friction - fwd.y * app->frame_delta * pr->accelerate
	};
	p->dir = (t_vec2){sinf(p->angle.x), -cosf(p->angle.x)};
	p->plane = (t_vec2){-p->dir.y * p->fov, p->dir.x * p->fov};
	player_collide(app, app->frame_delta);
	normalize_angle(&p->angle.x, false);
}
