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
# include <entity/entity.h>

struct	s_app;
struct	s_player;
struct	s_render_ent_data;

////////////////////////////////////////////////////////////////////////////////
// Render                                                                     //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Render Render
 * @{
 */

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
}	t_ray;

/** @brief Maximum number of entities that can be processed */
# define MAX_ENTITIES 256

/** @brief Data for raycasted entities */
typedef struct s_ray_ent
{
	/** @brief Distance to player */
	float				dist;
	/** @brief Entity */
	const t_entity		*ent;

	/** @brief `1 / det(Transform Matrix)` */
	float				inv_det;
	/** @brief Position in player-local space */
	/** @brief  Translate */
	t_vec2				space;
	/** @brief Scale */
	t_vec2				trans;
	/** @brief Screen X center coordinate */
	float				screen_x;
	/** @brief Draw start X screen position (Unclamped) */
	int					real_start_x;
	/** @brief Draw start X screen position */
	int					start_x;
	/** @brief Draw end X screen position */
	int					end_x;
	/** @brief Draw start Y screen position */
	int					start_y;
	/** @brief Draw end Y screen position */
	int					end_y;
	/** @brief Width scale factor */
	int					w;
	/** @brief Height scale factor */
	int					h;
	/** @brief Entity sprite */
	t_sprite			sprite;
	/** @brief Render flipped sprite */
	bool				flip;
}	t_ray_ent;

/** @brief Initialize a ray using screen width coordinate */
void
ray_init(const struct s_player *p, float camera_x, t_ray *r);
/** @brief Initialize a ray using arbitrary vectors */
void
ray_init_vec(t_vec2 pos, t_vec2 dir, t_ray *r);
/** @brief Cast a ray */
void
ray_cast(struct s_app *app, t_ray *r);
/** @brief Ray algorithm for entities */
void
ray_cast_entities(struct s_app *app, struct s_render_ent_data *render);

/** @brief Render a frame */
void
render_frame(struct s_app *app);
/** @brief Render a single veritcal slice */
void
render_slice(struct s_app *app, int x, const t_ray *r);
/** @brief Render a wall */
void
render_wall(struct s_app *app, int x, const t_ray *ray);
/** @brief Render entieies */
void
render_entities(struct s_app *app);

/******************************************************************************/
/* Internals                                                                  */
/******************************************************************************/

struct s_render_wall_data
{
	int				line_h;
	/** @brief Draw top screen vertical position */
	int				ds;
	/** @briof Draw end screen vertical poosition */
	int				de;

	int				tw;
	int				th;
	int				tx;
	int				ty;
	float			wall_x;
	uint32_t		*pix;
	const t_texture	*tex;
};

/** @brief Entity render data */
struct s_render_ent_data
{
	/** @brief Entities to render */
	t_ray_ent	ents[MAX_ENTITIES];
	/** @brief Number of entities to render */
	size_t		num;
};

/** @brief Entity RBTree traversal data */
struct s_ent_tr_data
{
	const struct s_app			*app;
	struct s_render_ent_data	*render;
};

/** @} */

#endif // RENDER_H
