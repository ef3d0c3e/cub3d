/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_BONUS_H
# define MAP_BONUS_H

# include <util/util_bonus.h>
# include <assets/assets_bonus.h>

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
	/** @brief Whether pitch is enabled */
	int		pitch_enabled;
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
	/** @brief Data for each tile */
	t_rbtree			map_state;

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

/**
 * @defgroup MapState Map State
 * @ingroup Map
 * @{
 */

/** @brief Base data for map state */
typedef struct s_map_state_base
{
	/** @brief Function to update the map */
	void	(*update_fn)(void *this, struct s_app *app);
}	t_map_state_base;

/** @brief Door state */
struct s_map_state_door
{
	/** @brief Base data for dynamic dispatch */
	const t_map_state_base	*base;
	/** @brief Open stage: `0` -> closed, `1` -> fully open */
	float					open;
	/** @brief Door direction: `0` -> static, `1` -> opening, `-1` -> closing */
	int						direction;
	/** @brief Frame when the door should star closing */
	size_t					close_time;
};
/** @brief Create a default @ref s_map_state_door */
void
*map_state_door(void);
/**
 * @brief Interact with the door
 *
 * @param this Door
 */
void
map_state_door_interact(void *this, struct s_app *app);

/**
 * @brief Update states for the entire map
 * This function must be called every frame to tick map states
 *
 * @param app Application pointer
 */
void
map_state_update(struct s_app *app);
/**
 * @brief Map state key comparison function
 *
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return `lhs <=> rhs`
 */
int
map_state_cmp(const void *lhs, const void *rhs);
/**
 * @brief Get tile state from the map
 *
 * @param app Application pointer
 * @param x X coordinate
 * @param y Y coordinate
 * @return Map state at `(x, y)`, or `NULL`
 */
void
*map_state_get(struct s_app *app, int x, int y);
/**
 * @brief Set tile data for the map
 *
 * @param app Application pointer
 * @param x X coordinate
 * @param y Y coordinate
 * @param state State to set
 */
void
map_state_set(struct s_app *app, int x, int y, void *state);

/** @} */

/** @} */

#endif // MAP_BONUS_H
