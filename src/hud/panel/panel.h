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

struct					s_app;

////////////////////////////////////////////////////////////////////////////////
// Panel                                                                      //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Panel Panel drawing utilities
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// Bounding Boxes                                                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup BBoxPanel Bounding Boxes
 * @ingroup Panel
 * @{
 */

/** @brief A bounding box */
typedef struct s_bbox
{
	/** @brief Top-Left corner position */
	t_vec2	pos;
	/** @brief Bounding box sizes */
	t_vec2	size;
}	t_bbox;

/**
 * @brief Create a bounding box
 *
 * @param pos BBox position
 * @param size BBox size
 * @param padding Optional pixel padding (Top, Right, Bottom, Left)
 * @param border Optional border size
 * @return New bounding box
 */
t_bbox
pan_bbox(t_vec2 pos, t_vec2 size, const int *padding, int border);
/**
 * @brief Compute the screen coordinates of a bounding box
 *
 * @param bbox Bounding box
 * @param screen_pos Screen Top-Left coordinates
 * @param screen_size Screen pixel sizes
 */
void
pan_bbox_screen(const t_bbox *bbox, t_pos *screen_pos, t_pos *screen_size);
/**
 * @brief Get the center point of a bounding box
 *
 * @param bbox Bounding box
 * @return The center of @p bbox
 */
t_vec2
pan_bbox_center(const t_bbox *bbox);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Widgets                                                                    //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup WidgetsPanel Widgets
 * @ingroup Panel
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// Button                                                                     //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup ButtonPanel Button
 * @ingroup WidgetsPanel
 * @{
 */

/** @brief Button styling */
typedef struct s_hud_style_button
{
	/** @brief Top, Right, Bottom, Left padding in pixels */
	int		padding[4];
	/** @brief Button rectangle border radius */
	int		radius;
	/** @brief Button color/boder for Default/Hovered/Active */
	t_color	colors[6];
	/** @brief Button border size */
	int		border_size;
}	t_hud_style_button;

/**
 * @brief Default style for buttons
 *
 * @return The default style for buttons
 */
t_hud_style_button
pan_button_style(void);
/**
 * @brief Add a button to the UI
 *
 * @param text Button text
 * @return `true` if the button was clicked, `false` otherwise
 */
bool
pan_button(const char *text);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Text                                                                       //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup TextPanel Text
 * @ingroup WidgetsPanel
 * @{
 */

void
pan_text(const char *text);

/** @} */

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Layout                                                                     //
////////////////////////////////////////////////////////////////////////////////

/** @brief Internal ID for Panel */
typedef unsigned int	t_pan_id;

/**
 * @defgroup LayoutPanel Layout
 * @ingroup Panel
 * @{
 */

enum e_panel_layout
{
	LAYOUT_VERTICAL,
	LAYOUT_HORIZONTAL,
	LAYOUT_COLUMNS,
};

typedef struct s_pan_layout
{
	/** @brief Layout type */
	enum e_panel_layout	type;
	/** @brief Available space */
	t_bbox				rect;

	/** @brief Number of vertical columns */
	int					col_count;
	/** @brief Current vertical columns */
	int					col_id;
	/** @brief Maximum used vertical space */
	float				vertical_space;
}	t_pan_layout;

/**
 * @brief Start a column layout
 *
 * @param id Columns ID
 * @param n Number of columns
 */
void
pan_push_columns(const char *id, int n);
/**
 * @brief Move to the next column
 */
void
pan_next_columns(void);
/**
 * @brief Stop the column layout
 */
void
pan_pop_columns(void);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Panel Context                                                              //
////////////////////////////////////////////////////////////////////////////////

enum
{
	/** @brief Size of Panel's id stack */
	PAN_ID_SIZE = 32,
};

/** @brief HUD draw context */
typedef struct s_panel_ctx
{
	/** @brief Application */
	struct s_app		*app;
	/** @brief Current draw position */
	t_vec2				cursor;
	/** @brief Current scale */
	t_vec2				scale;
	/** @brief Current font */
	t_font				font;
	/** @brief Height of a line (as a fraction of the vertical space) */
	float				line_height;
	/** @brief Top/Bottom padding */
	int					padding[2];

	/** @brief Stack of IDs */
	t_pan_id			id_stack[PAN_ID_SIZE];
	/** @brief Depth in @ref id_stack */
	size_t				id_stack_depth;
	/** @brief Active widget ID */
	t_pan_id			active;

	/** @brief Stack of IDs */
	t_pan_layout		layout_stack[PAN_ID_SIZE];
	/** @brief Depth in @ref id_stack */
	size_t				layout_stack_size;

	/** Button style */
	t_hud_style_button	st_button;
}	t_panel_ctx;

/**
 * @brief Initialize Panel
 *
 * @param app Application pointer
 * @param line_size Desired line height (as a fraction of the vertical space)
 * @param padding Base top/bottom padding for text
 */
void
pan_init(struct s_app *app, float line_size, const int padding[2]);
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
 * @brief Compute the id for an integer
 *
 * @param id Integer to compute the ID of
 * @return The id of the integer in the current context
 */
t_pan_id
pan_id_int(int id);
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
 * @param drawable Drawable
 * @return The size of @p drawable
 */
t_vec2
pan_drawable_size(const t_drawable *drawable);
/**
 * @brief Draw a list of @ref t_draw_item on screen
 *
 * @param drawable The list of @ref t_draw_item
 * @param offset The offset to apply to each @ref t_draw_item
 */
void
pan_drawable_draw(const t_drawable *drawable, t_vec2 offset);

////////////////////////////////////////////////////////////////////////////////
// Panel Utils                                                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Check if the area delimited by the bouding box is under the mouse
 * cursor
 *
 * @param bbox Bounding box
 * @return `true` if the rectangle delimited by @p bbox is under the
 * mouse cursor, `false` otherwise
 */
bool
pan_mouse_hovered(const t_bbox *bbox);
bool
pan_is_active(void);

/** @} */

#endif // PANEL_H
