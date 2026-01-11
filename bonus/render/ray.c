/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	ray_init(const t_player *p, float camera_x, t_ray *r)
{
	ft_memset(r, 0, sizeof(t_ray));
	r->map_x = (int)p->position.x;
	r->map_y = (int)p->position.y;
	r->ray = (t_vec2){p->dir.x + p->plane.x * camera_x,
		p->dir.y + p->plane.y * camera_x};
	r->delta_dist = (t_vec2){1e10f, 1e10f};
	if (r->ray.x != 0)
		r->delta_dist.x = fabsf(1.f / r->ray.x);
	if (r->ray.y != 0)
		r->delta_dist.y = fabsf(1.f / r->ray.y);
	r->step_x = -(r->ray.x < 0) + (r->ray.x >= 0);
	r->step_y = -(r->ray.y < 0) + (r->ray.y >= 0);
	if (r->ray.x < 0)
		r->side_dist.x = (p->position.x - (float)r->map_x) * r->delta_dist.x;
	else
		r->side_dist.x = ((float)r->map_x + 1.f - p->position.x)
			* r->delta_dist.x;
	if (r->ray.y < 0)
		r->side_dist.y = (p->position.y - (float)r->map_y)
			* r->delta_dist.y;
	else
		r->side_dist.y = ((float)r->map_y + 1.f - p->position.y)
			* r->delta_dist.y;
}

void
	ray_init_vec(t_vec2 pos, t_vec2 dir, t_ray *r)
{
	ft_memset(r, 0, sizeof(*r));
	r->map_x = (int)pos.x;
	r->map_y = (int)pos.y;
	r->ray = dir;
	r->delta_dist = (t_vec2){1e10f, 1e10f};
	if (r->ray.x != 0)
		r->delta_dist.x = fabsf(1.f / dir.x);
	if (r->ray.y != 0)
		r->delta_dist.y = fabsf(1.f / dir.y);
	r->step_x = -(r->ray.x < 0) + (r->ray.x >= 0);
	r->step_y = -(r->ray.y < 0) + (r->ray.y >= 0);
	if (r->ray.x < 0)
		r->side_dist.x = (pos.x - (float)r->map_x) * r->delta_dist.x;
	else
		r->side_dist.x = ((float)r->map_x + 1.f - pos.x) * r->delta_dist.x;
	if (r->ray.y < 0)
		r->side_dist.y = (pos.y - (float)r->map_y) * r->delta_dist.y;
	else
		r->side_dist.y = ((float)r->map_y + 1.f - pos.y) * r->delta_dist.y;
}

static void
	ray_door(t_app *app, t_ray *r, const struct s_map_state_door *door)
{
	const t_pos				slide_axis = (t_pos[4]){{-1, 0}, {0, 1}, {1, 0},
	{0, -1}}[r->hit->orientation];
	const t_player			*player = &app->game.player;
	t_vec2					exact;
	float					door_coord;

	if (r->side == 0)
	{
		exact.x = (float)(r->map_x + (r->step_x <= 0));
		exact.y = player->position.y + (exact.x - player->position.x)
			* r->ray.y / r->ray.x;
	}
	else
	{
		exact.y = (float)(r->map_y + (r->step_y <= 0));
		exact.x = player->position.x + (exact.y - player->position.y)
			* r->ray.x / r->ray.y;
	}
	door_coord = (slide_axis.y != 0) * (exact.y - (float)r->map_y)
		+ (slide_axis.y == 0) * (exact.x - (float)r->map_x);
	if ((slide_axis.x < 0 || slide_axis.y < 0) * (door_coord < door->open)
		+ (slide_axis.x >= 0 && slide_axis.y >= 0)
		* (door_coord > (1.f - door->open)))
		r->hit = NULL;
}

void
	ray_cast(t_app *app, t_ray *r)
{
	int	df;

	while (!r->hit)
	{
		df = r->side_dist.x < r->side_dist.y;
		r->side_dist.x += (float)df * r->delta_dist.x;
		r->side_dist.y += !df * r->delta_dist.y;
		r->map_x += df * r->step_x;
		r->map_y += !df * r->step_y;
		r->side = !df;
		if (r->map_x < 0 || r->map_x >= app->map.size_x
			|| r->map_y < 0 || r->map_y >= app->map.size_y)
			break ;
		r->hit = map_get(app, r->map_x, r->map_y);
		if (r->hit && r->hit->type == MAT_FLOOR)
			r->hit = NULL;
		if (r->hit && r->hit->type == MAT_DOOR)
			ray_door(app, r, map_state_get(app, r->map_x, r->map_y));
	}
	r->perp_dist = 1e10;
	if (!r->hit)
		return ;
	r->perp_dist = !r->side * (r->side_dist.x - r->delta_dist.x)
		+ !!r->side * (r->side_dist.y - r->delta_dist.y);
	r->perp_dist = clampf(r->perp_dist, 0.001f, 1e10f);
}
