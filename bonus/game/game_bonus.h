/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include <player/player_bonus.h>
# include <assets/assets_bonus.h>

////////////////////////////////////////////////////////////////////////////////
// Game data                                                                  //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Game Game data
 * @{
 */

struct	s_app;

typedef struct s_game
{
	/** @brief The minimap base texture */
	t_sprite	minimap;

	/** @brief The player */
	t_player	player;

	/** @brief Show the minimap */
	bool		show_minimap;

	/** @brief Infinite ammo mode */
	bool		infinite_ammo;
}	t_game;

/**
 * @brief Setup the game component
 *
 * @param app Application pointer
 * @return `true` on success, `false` on errors
 */
bool
game_setup(struct s_app *app);
/**
 * @brief Cleanup the game component
 *
 * @param app Application pointer
 */
void
game_cleanup(struct s_app *app);

void
game_input(struct s_app *app);
void
game_ui(struct s_app *app);
/**
 * @brief Process environment interactions
 *
 * @param app Application pointer
 */
void
game_interact(struct s_app *app);
/**
 * @brief Show the game's debug menu
 *
 * @param app Application pointer
 */
void
game_debug(struct s_app *app);

/**
 * @brief Setup the minimap
 *
 * @param app Application pointer
 * @return `true` on success, `false` on errors
 */
bool
game_minimap_setup(struct s_app *app);
/**
 * @brief Render the minimap
 *
 * @param app Application pointer
 */
void
game_minimap_render(struct s_app *app);

/**
 * @brief Display action text
 *
 * @param app Application pointer
 * @param text Text to display
 */
void
action_text(struct s_app *app, const char *text);

/** @} */

#endif // GAME_BONUS_H
