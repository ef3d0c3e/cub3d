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

/** @brief Draw parameters */
typedef struct s_draw_params
{
	/** @brief Draw origin */
	t_vec2	origin;
	/** @brief Draw scale */
	t_vec2	scale;
	/** @brief Custom color */
	t_color	color;
}	t_draw_params;

/**
 * @brief Draw a sprite on screen
 *
 * @param app Application pointer
 * @param spr Sprite to draw
 * @param p Draw parameters
 */
void
hud_draw_sprite(
	struct s_app *app,
	const t_sprite *spr,
	t_draw_params p);
/**
 * @brief Draw a sprite on screen with bilinear sampling
 *
 * @param app Application pointer
 * @param spr Sprite to draw
 * @param p Draw parameters
 */
void
hud_draw_sprite_bilinear(
	struct s_app *app,
	const t_sprite *spr,
	t_draw_params p);

/** @brief Drawable primitives */
enum e_draw_item
{
	/** @brief Text */
	DRAW_TEXT,
	/** @brief Text with shadow */
	DRAW_TEXT_SHADOW,
};

/** @brief Drawawable primitive data */
typedef struct s_draw_item
{
	/** @brief Drawable type */
	enum e_draw_item	type;
	union u_draw_item
	{
		/** @brief Drawable text */
		struct s_draw_item_text
		{
			/** @brief Text position */
			t_vec2		pos;
			/** @brief Text scale */
			float		scale;
			/** @brief Text color */
			t_color		color;
			const char	*text;
		}	text;
		/** @brief Drawable text */
		struct s_draw_item_shadow
		{
			/** @brief Text position */
			t_vec2		pos;
			/** @brief Text scale */
			float		scale;
			/** @brief Text color */
			t_color		color;
			/** @brief Text shadow color */
			t_color		color_shadow;
			const char	*text;
		}	text_shadow;
	}	draw;
}	t_draw_item;

/** @brief A queue holding all elements that need to be drawn */
typedef struct s_draw_queue
{
	/** @brief Items to draw */
	t_draw_item	*items;
	/** @brief Number items */
	size_t		size;
	/** @brief Capacity of @ref items */
	size_t		capacity;
}	t_draw_queue;

/**
 * @brief Add an item to the HUD's @ref t_draw_queue
 *
 * @param app Application pointer
 * @param item Item to draw
 * @return A pointer to the inserter @ref t_draw_item
 */
t_draw_item
*hud_draw(struct s_app *app, t_draw_item item);
/**
 * @brief Render the HUD from the @ref t_draw_queue
 *
 * @param app Application pointer
 */
void
hud_render(struct s_app *app);

/**
 * @brief Draw function for @ref DRAW_TEXT
 *
 * @param app Application pointer
 * @param item @ref DRAW_TEXT to draw
 */
void
hud_draw_text(struct s_app *app, const t_draw_item *item);
/**
 * @brief Draw function for @ref DRAW_TEXT_SHADOW
 *
 * @param app Application pointer
 * @param item @ref DRAW_TEXT_SHADOW to draw
 */
void
hud_draw_text_shadow(struct s_app *app, const t_draw_item *item);

/**
 * @brief Convenience function to display text on the screen, bypassing the draw
 * queue
 *
 * @param app Application pointer
 * @param pos Text TopLeft origin
 * @param text Text to display
 * @param s Text scale
 */
void
hud_text(struct s_app *app, t_pos pos, const char *text, float s);
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
	float			scale;
	/** @brief HUD draw queue */
	t_draw_queue	queue;
}	t_hud;

/**
 * @brief Initalize the HUD
 *
 * @param app Application pointer
 */
void
hud_init(struct s_app *app);
/**
 * @brief Free the HUD
 *
 * @param app Application pointer
 */
void
hud_free(struct s_app *app);

/** @} */

#endif // HUD_H
