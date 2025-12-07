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
 * @defgroup HUD HUD
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// HUD Draw                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup DrawHUD HUD Draw helpers
 * @ingroup HUD
 * @{
 */

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
/**
 * @brief Display text on the screen
 *
 * @param app Application pointer
 * @param pos Text TopLeft origin
 * @param text Text to display
 * @param s Text scale
 */
void
hud_texts(struct s_app *app, t_pos pos, const char *text, float s);
/**
 * @brief Compute the size of text
 *
 * @param app Application pointer
 * @param text Text to compute the size of
 * @return The size of `text`
 */
t_vec2
hud_textsize(struct s_app *app, const char *text);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// HUD                                                                        //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_hud
{
	/** @brief HUD scaling */
	float	scale;
}	t_hud;

/**
 * @brief Initalize the HUD
 *
 * @param app Application pointer
 */
void
hud_init(struct s_app *app);
/**
 * @brief Draw the HUD
 *
 * @param app Application pointer
 */
void
hud_draw(struct s_app *app);

/** @} */

#endif // HUD_H
