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
	size_t	i;

	ft_memset(r, 0, sizeof(t_ray));
	r->map_x = (int)p->position.x;
	r->map_y = (int)p->position.y;
	r->ray = (t_vec2){p->dir.x + p->plane.x * camera_x,
		p->dir.y + p->plane.y * camera_x};
	r->delta_dist = (t_vec2){1e30, 1e30};
	if (r->ray.x != 0)
		r->delta_dist.x = fabsf(1.f / r->ray.x);
	if (r->ray.y != 0)
		r->delta_dist.y = fabsf(1.f / r->ray.y);
	r->step_x = -(r->ray.x < 0) + (r->ray.x >= 0);
	r->step_y = -(r->ray.y < 0) + (r->ray.y >= 0);
	if (r->ray.x < 0)
		r->side_dist.x = (p->position.x - (float)r->map_x) * r->delta_dist.x;
	else
		r->side_dist.x = ((float)r->map_x + 1.f - p->position.x) * r->delta_dist.x;
	if (r->ray.y < 0)
		r->side_dist.y = (p->position.y - (float)r->map_y) * r->delta_dist.y;
	else
		r->side_dist.y = ((float)r->map_y + 1.f - p->position.y) * r->delta_dist.y;
	i = 0;
	while (i <= MAX_ENTITIES)
		r->s_ent[i++].dist = 1e10;
	r->ent_num = 0;
}

void
	ray_init_vec(t_vec2 pos, t_vec2 dir, t_ray *r)
{
	size_t	i;

	ft_memset(r, 0, sizeof(t_ray));
	r->map_x = (int)pos.x;
	r->map_y = (int)pos.y;
	r->ray = dir;
	r->delta_dist = (t_vec2){1e10, 1e10};
	if (r->ray.x != 0)
		r->delta_dist.x = fabsf(1.f / dir.x);
	if (r->ray.y != 0)
		r->delta_dist.y = fabsf(1.f / dir.y);;
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
	i = 0;
	while (i <= MAX_ENTITIES)
		r->s_ent[i++].dist = 1e10;
	r->ent_num = 0;
}

/** @brief Ray algorithm for walls */
static void
	ray_dda(const t_app *app, t_ray *r)
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
	}
	r->perp_dist = 1e10;
	if (!r->hit)
		return ;
	r->perp_dist = !r->side * (r->side_dist.x - r->delta_dist.x)
		+ !!r->side * (r->side_dist.y - r->delta_dist.y);
	if (r->perp_dist < 0.001f)
		r->perp_dist = 0.001f;
}

void
	ray_cast(const t_app *app, int x, t_ray *r)
{
	ray_dda(app, r);
	//ray_cast_ent(app, x, r);
}
