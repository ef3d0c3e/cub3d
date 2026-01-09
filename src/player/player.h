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

/** @brief Player bounding box size */
#define PLAYER_SIZE 0.3

/** @brief Data for the player's weapons */
typedef struct s_player_weapondata
{
	/** @brief Set to `true` if the player possesses the weapon */
	bool				has_weapon;
	/** @brief Number of ammunitions */
	int					ammo;
	/** @brief Animation state */
	t_pos				anim;
}	t_player_weapondata;

typedef struct s_player
{
	/** @brief Player field of view */
	float				fov;
	/** @brief Acceleration (m/s²) */
	t_vec2				accel;
	/** @brief Velocity (m/s) */
	t_vec2				velocity;
	/** @brief Position (m) */
	t_vec2				position;
	/** @brief View angles (yaw, pitch) */
	t_vec2				angle;
	/** @brief Pitch Y offset */
	int					pitch;
	/** @brief Player direction (X, Y) */
	t_vec2				dir;
	/** @brief Player plane (X, Y) */
	t_vec2				plane;

	/** @brief Player's health */
	int					health;

	/** @brief Available weapons */
	t_player_weapondata	weapons[WEAPON_NUM_];
	/** @brief Current weapon */
	enum e_weapon_id	weapon_id;
	/** @brief Time left for the shooting animation */
	float				weapon_anim;
	/** @brief Player immunity time */
	float				immunity;
}	t_player;

/**
 * @brief Setup the player
 *
 * @param app Application pointer
 */
void
player_setup(struct s_app *app);
/**
 * @brief Process player inputs
 *
 * @param app Application pointer
 */
void
player_input(struct s_app *app);
/**
 * @brief Update player movements
 *
 * @param app Application pointer
 * @param move Movement from inputs
 */
void
player_move(struct s_app *app, t_vec2 move);

#endif // PLAYER_H
