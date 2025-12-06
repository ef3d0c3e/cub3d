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
	/** @brief Material atlas */
	t_material_atlas	material_atlas;
	/** @brief Texture atlas */
	t_texture_atlas		texture_atlas;
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
 * @param mlx_ptr The mlx instance
 * @param map The map
 */
void
map_free(void *mlx_ptr, t_map *map);
/**
 * @brief Load map assets from disk
 *
 * @param mlx_ptr The mlx instance
 * @param map The map
 * @return `true` on success, `false` on errors
 */
bool
map_load_assets(void *mlx_ptr, t_map *map);

/** @} */

#endif // MAP_H
