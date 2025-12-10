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

struct						s_app;
typedef struct s_draw_item	t_draw_item;

/**
 * @defgroup HUD HUD
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// HUD Draw                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup DrawHUD HUD Drawing
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

/** @brief Text font */
typedef struct s_font
{
	/** @brief Font base texture */
	const t_texture	*texture;
	/** @brief Background color */
	t_color			background;
	/** @brief Number of `(colums, rows)` of the font */
	t_pos			geom;
	/** @brief Base color of the font */
	t_color			color;
	/** @brief Font X/Y scaling */
	t_vec2			scale;
	/** @brief Font cell size */
	t_pos			base_size;
	/** @brief Scaled cell size */
	t_pos			size;
}	t_font;

/**
 * @brief Create a new font
 *
 * @param base Base font
 * @param color Font base color
 * @param scale Scale of the font
 * @return New font
 */
t_font
font_new(const t_font *base, t_color color, float scale);
/**
 * @brief Make a text @ref t_draw_item with a font
 *
 * @param font The font to use
 * @param pos Coordinates of the text
 * @param text Text to draw
 *
 * @returns A @ref t_draw_item for `text`
 */
t_draw_item
font_text(t_font font, t_vec2 pos, const char *text);
/**
 * @brief Make a text @ref t_draw_item with a font with shadow
 *
 * @param font The font to use
 * @param pos Coordinates of the text
 * @param text Text to draw
 * @param color_shadow Shadow color
 *
 * @returns A @ref t_draw_item for `text`
 */
t_draw_item
font_text_shadow(
	t_font font,
	t_vec2 pos,
	const char *text,
	t_color color_shadow);
/**
 * @brief Get a sprite from a font
 *
 * @param font Font to get a sprite for
 * @param ch Character to get a sprite for
 * @return Sprite corresponding to @p ch in @p font
 */
t_sprite
font_get(const t_font *font, int ch);
/**
 * @brief Get the size of text
 *
 * @param app Application pointer
 * @param font Font
 * @param text Text
 * @return The size of @p test in @p font
 */
t_vec2
font_textsize(const struct s_app *app, const t_font *font, const char *text);

/** @brief Drawable primitives */
enum e_draw_item
{
	/** @brief Text */
	DRAW_TEXT,
	/** @brief Text with shadow */
	DRAW_TEXT_SHADOW,
	/** @brief Sprite */
	DRAW_SPRITE,
	/** @brief Rectangle */
	DRAW_RECT,
	/** @brief Rounded rectangle */
	DRAW_RECT_RADIUS,
};

/** @brief Drawable primitive data */
struct s_draw_item
{
	/** @brief Drawable type */
	enum e_draw_item	type;
	union u_draw_item
	{
		/** @brief Drawable text */
		struct s_draw_item_text
		{
			/** @brief Text font */
			t_font		font;
			/** @brief Text position */
			t_vec2		pos;
			/** @brief Text to draw */
			const char	*text;
		}	text;
		/** @brief Drawable text */
		struct s_draw_item_shadow
		{
			/** @brief Text font */
			t_font		font;
			/** @brief Text position */
			t_vec2		pos;
			/** @brief Text to draw */
			const char	*text;
			/** @brief Text shadow color */
			t_color		color_shadow;
		}	text_shadow;
		/** @brief Drawable sprite */
		struct s_draw_item_sprite
		{
			/** @brief Sprite to draw */
			t_sprite	sprite;
			/** @brief Sprite coordinates */
			t_vec2		pos;
			/** @brief Sprite X/Y scale */
			t_vec2		scale;
			/** @brief Sprite color */
			t_color		color;
		}	sprite;
		/** @brief Drawable rectangle */
		struct s_draw_item_rect
		{
			/** @brief Top-Left corner */
			t_vec2		pos;
			/** @brief X/Y sizes of the rectangle */
			t_vec2		size;
			/** @brief Interior color */
			t_color		color;
		}	rect;
		/** @brief Drawable rounded rectangle */
		struct s_draw_item_rect_radius
		{
			/** @brief Top-Left corner */
			t_vec2		pos;
			/** @brief X/Y sizes of the rectangle */
			t_vec2		size;
			/** @brief Border radius of the rectangle */
			int			radius;
			/** @brief Interior color */
			t_color		color;
			/** @brief Outline color */
			t_color		border;
			/** @brief Outline pixel size */
			int			border_size;
		}	rect_radius;
	}	draw;
};

/**
 * @brief Get the size of a @ref t_draw_item
 *
 * @param app Application pointer
 * @param item Item to get the size of
 * @return The size of @p item in screen UV space
 */
t_vec2
draw_item_size(const struct s_app *app, const t_draw_item *item);
/**
 * @brief Offset the position of a @ref t_draw_item
 *
 * @param app Application pointer
 * @param item Item to offset
 * @param offset Offeset (in screen-space UV) to apply to @p item
 * @returns The offseted draw item
 */
t_draw_item
draw_item_offset(const struct s_app *app, t_draw_item item, t_vec2 offset);

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

/* --- Draw functions --- */

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
 * @brief Draw function for @ref DRAW_SPRITE
 *
 * @param app Application pointer
 * @param item @ref DRAW_SPRITE to draw
 */
void
hud_draw_sprite_item(struct s_app *app, const t_draw_item *item);
/**
 * @brief Draw function for @ref DRAW_RECT
 *
 * @param app Application pointer
 * @param item @ref DRAW_RECT to draw
 */
void
hud_draw_rect(struct s_app *app, const t_draw_item *item);
/**
 * @brief Draw function for @ref DRAW_RECT_RADIUS
 *
 * @param app Application pointer
 * @param item @ref DRAW_RECT_RADIUS to draw
 */
void
hud_draw_rect_radius(struct s_app *app, const t_draw_item *item);

/* --- Misc --- */

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
	/** @brief The base hud font */
	t_font			font;
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

void
hud_menu_move(const char ***items, t_pos *selected, t_pos move);
void
hud_menu(struct s_app *app, const char ***items, t_pos selected);

/** @} */

#endif // HUD_H
