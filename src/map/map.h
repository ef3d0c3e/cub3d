/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_H
# define MAP_H

# include <util/util.h>
# include <assets/assets.h>

struct	s_app;

/**
 * @defgroup Map Map
 * @{
 */

/** @brief Custom map properties */
typedef struct s_map_props
{
	/** @brief Accelerate factor */
	float	accelerate;
	/** @brief Ground friction */
	float	friction;
	/** @brief Ideal frame time in seconds */
	float	frame_time;
	/** @brief Material for the player's spawn point */
	char	player_spawn;
}	t_map_props;

/** @brief The Cub3D map */
typedef struct s_map
{
	/** @brief Default color for floor/ceiling */
	t_color				colors[2];

	/** @brief X-size of the map */
	int					size_x;
	/** @brief Y-size of the map */
	int					size_y;
	/** @brief The map content */
	t_atlas_id			*map;

	/** @brief The player's spawn point */
	t_pos				player_spawn;
	/** @brief The player's spawn rotation */
	enum e_orientation	player_orientation;

	/** @brief Custom properties for the map */
	t_map_props			props;
}	t_map;

/**
 * @brief Free the map
 *
 * @param map The map
 */
void
map_free(t_map *map);
/**
 * @brief Get a material at a given position in the map
 *
 * @param app Application pointer
 * @param x X coordinate
 * @param y Y coordinate
 * @return The material at `(x, y)`, or `NULL` for empty spaces
 */
t_material
*map_get(const struct s_app *app, int x, int y);

/** @} */

#endif // MAP_H
