/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include <map/map.h>

struct	s_app;
struct	s_player;

////////////////////////////////////////////////////////////////////////////////
// Render                                                                     //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Render Render
 * @{
 */

# define MAX_ENTITIES 16

/** @brief Ray casting data */
typedef struct s_ray
{
	/* -- Ray input parameters -- */
	/* Ray direction */
	t_vec2		ray;
	int			step_x;
	int			step_y;
	/* Map coordinates */
	int			map_x;
	int			map_y;

	/* -- DDA values -- */
	t_vec2		delta_dist;
	t_vec2		side_dist;
	int			side;

	/* -- Output -- */
	/* Hit wall */
	t_material	*hit;
	float		perp_dist;

	/* -- Entity collisions -- */
	struct
	{
		float	dist;
		void	*ent;
	}			s_ent[MAX_ENTITIES];
	size_t		ent_num;
}	t_ray;

/** @brief Initializes a ray using screen width coordinate */
void
ray_init(const struct s_player *p, float camera_x, t_ray *r);
/** @brief Initializes a ray using arbitrary vectors */
void
ray_init_vec(t_vec2 pos, t_vec2 dir, t_ray *r);
/** @brief Casts a ray */
void
ray_cast(const struct s_app *app, int x, t_ray *r);
/** @brief Ray algorithm for entities */
void
ray_cast_ent(const struct s_app *app, int x, t_ray *r);

/** @brief Renders a frame */
void
render_frame(struct s_app *app);
void
render_wall(struct s_app *app, int x, const t_ray *ray);
void
render_entity(struct s_app *app, int x, void *ent);

/******************************************************************************/
/* Internals                                                                  */
/******************************************************************************/

struct s_ray_ent_data
{
	float	inv;
	float	screen_x;
	t_vec2	space;
	t_vec2	trans;
	int		w;
	int		start_x;
	int		end_x;
};

struct s_render_wall_data
{
	int				line_h;
	int				ds;
	int				de;

	int				tex_id;
	int				tw;
	int				th;
	int				tx;
	int				ty;
	float			wall_x;
	uint32_t		*pix;
	const t_texture	*tex;
};

struct s_render_ent_data
{
	float			inv_det;
	t_vec2			space;
	t_vec2			trans;
	float			screen_x;
	int				sprite_w;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
	int				line_h;
	int				fx;
	int				fy;
	int				fw;
	int				fh;
	uint32_t		*pixels;
	const t_sprite	*spr;
	int				tx;
	int				ty;
};

/** @} */

#endif // RENDER_H
