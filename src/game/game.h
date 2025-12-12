/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GAME_H
# define GAME_H


# include <player/player.h>
# include <assets/assets.h>

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
game_render(struct s_app *app);
/**
 * @brief Show the game's debug menu
 *
 * @param app Application pointer
 */
void
game_debug(struct s_app *app);

/** @} */

#endif // GAME_H
