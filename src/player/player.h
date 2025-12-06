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

# include <util/util.h>

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
}	t_player;

#endif // PLAYER_H

