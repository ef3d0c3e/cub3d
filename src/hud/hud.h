/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HUD_H
# define HUD_H

# include <util/util.h>
# include <assets/assets.h>

struct	s_app;

/**
 * @brief Display a sprite on screen
 *
 * @param app Application pointer
 * @param spr Sprite to display
 * @param origin Sprite origin (relative to the screen)
 * @param scale Sprite scale
 */
void
hud_blit(struct s_app *app, const t_sprite *spr, t_vec2 origin, t_vec2 scale);

/**
 * @brief Display text on the screen
 *
 * @param app Application pointer
 * @param pos Text TopLeft origin
 * @param text Text to display
 */
void
hud_text(struct s_app *app, t_pos pos, const char *text);

#endif // HUD_H
