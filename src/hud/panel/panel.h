/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PANEL_H
# define PANEL_H

# include <hud/hud.h>

struct	s_app;

////////////////////////////////////////////////////////////////////////////////
// Panel                                                                      //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Panel Panel drawing utilities
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// Button                                                                     //
////////////////////////////////////////////////////////////////////////////////

/**
 *
 * @defgroup ButtonPanel Button
 * @ingroup Panel
 * @{
 */

/** @brief Button styling */
typedef struct s_hud_style_button
{
	/** @brief Top, Right, Bottom, Left padding in pixels */
	int		padding[4];
	/** @brief Button rectangle border radius */
	int		radius;
	/** @brief Button color */
	t_color	button_color;
	/** @brief Hovered button color */
	t_color	button_color_hover;
	/** @brief Active button color */
	t_color	button_color_active;
}	t_hud_style_button;

t_hud_style_button
pan_button_style(void);
bool
pan_button(const char *text);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Panel Context                                                              //
////////////////////////////////////////////////////////////////////////////////

typedef	unsigned int	t_pan_id;

enum
{
	/** @brief Size of Panel's id stack */
	PAN_ID_SIZE = 32,
};

/** @brief HUD draw context */
typedef struct s_panel_ctx
{
	/** @brief Application */
	struct s_app	*app;
	/** @brief Current draw position */
	t_vec2			cursor;
	/** @brief Current scale */
	t_vec2			scale;
	/** @brief Current font */
	t_font			font;

	/** @brief Stack of IDs */
	t_pan_id		id_stack[PAN_ID_SIZE];
	/** @brief Depth in @ref id_stack */
	size_t			id_stack_depth;

	/** Button style */
	t_hud_style_button	st_button;
}	t_panel_ctx;

/**
 * @brief Initialize Panel
 *
 * @param app Application pointer
 */
void
pan_init(struct s_app *app);
/**
 * @brief Get or set the global HUD context
 *
 * @param ctx If `NULL` does nothing, otherwise sets the global context to the
 * value contained in @p ctx
 * @return The global context
 */
t_panel_ctx
*pan_ctx(t_panel_ctx *ctx);
/**
 * @brief Reset the context
 *
 * When the frame done drawing, this function is used to reset the state of the
 * context for the next frame.
 *
 * @param app Application pointer
 */
void
pan_context_reset(struct s_app *app);

/**
 * @brief Compute the id for a string
 *
 * @param id String to compute the ID of
 * @return The id of the string in the current context
 */
t_pan_id
pan_id_str(const char *id);
/**
 * @brief Push an ID in the context
 *
 * @param id ID to push in the context
 */
void
pan_id_push(t_pan_id id);
/**
 * @brief Pop the last ID in the context
 */
void
pan_id_pop(void);

/** @brief A slice of drawable items */
typedef struct s_drawable
{
	/** @brief Items */
	const t_draw_item	*items;
	/** @brief Number of items */
	size_t				nitems;
}	t_drawable;

/**
 * @brief Compute the size of a drawable
 *
 * @param app Application pointer
 * @param drawable Drawable
 * @return The size of @p drawable
 */
t_vec2
pan_drawable_size(const struct s_app *app, const t_drawable *drawable);
/**
 * @brief Draw a list of @ref t_draw_item on screen
 *
 * @param app Application pointer
 * @param drawable The list of @ref t_draw_item
 * @param offset The offset to apply to each @ref t_draw_item
 */
void
pan_drawable_draw(struct s_app *app, const t_drawable *drawable, t_vec2 offset);

/** @} */

#endif // PANEL_H
