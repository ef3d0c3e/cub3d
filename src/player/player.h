/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYER_H
# define PLAYER_H

struct	s_app;

# include <util/util.h>
# include <assets/defs/defs.h>

typedef struct s_player
{
	/** @brief Acceleration (m/s²) */
	t_vec2		accel;
	/** @brief Velocity (m/s) */
	t_vec2		velocity;
	/** @brief Position (m) */
	t_vec2		position;
	/** @brief View angles (yaw, pitch) */
	t_vec2		angle;

	/** @brief Player's health */
	int			health;

	/** @brief Available weapons */
	t_weapon			weapons[WEAPON_NUM_];
	/** @brief Current weapon */
	enum e_weapon_id	weapon;
	/** @brief Time left for the shooting animation */
	float				weapon_anim;
}	t_player;

/**
 * @brief Setup the player
 *
 * @param app Application pointer
 */
void
player_setup(struct s_app *app);
void
player_input(struct s_app *app);

#endif // PLAYER_H
