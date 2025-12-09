/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UI_H
# define UI_H

# include <util/util.h>

struct				s_app;

/**
 * @defgroup UI UI
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// MLX Definitions                                                            //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup MLX MLX Definitions
 * @ingroup UI
 * @{
 */

/** @brief Enum for keycodes */
enum	e_keycode
{
	KEY_SPACE = ' ',
	KEY_A = 'a',
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_RETURN = 0xff0d,
	KEY_ESC = 0xff1b,
	KEY_KP_PLUS = 0xffab,
	KEY_KP_MINUS = 0xffad,
	KEY_SHIFT_LEFT = 0xffe1,
	KEY_SHIFT_RIGHT = 0xffe2,
	KEY_CTRL_LEFT = 0xffe3,
	KEY_CTRL_RIGHT = 0xffe4,
	/* Arrows */
	KEY_ARROW_LEFT = 65361,
	KEY_ARROW_UP,
	KEY_ARROW_RIGHT,
	KEY_ARROW_DOWN,
};

/** @brief Enum for mouse buttons */
enum e_mousecode
{
	MOUSE_NONE,
	MOUSE_LEFT = 1,
	MOUSE_MIDDLE = 2,
	MOUSE_RIGHT = 3,
	MOUSE_WHEEL_DOWN = 4,
	MOUSE_WHEEL_UP = 5,
};

/** @brief Xlib event codes */
enum e_eventcode
{
	EVENT_KEYDOWN = 2,
	EVENT_KEYUP = 3,
	EVENT_MOUSEDOWN = 4,
	EVENT_MOUSEUP = 5,
	EVENT_MOUSEMOVE = 6,
	EVENT_EXPOSE = 12,
	EVENT_DESTROY = 17,
	EVENT_CONFIGURE_REQUEST = 23,
	EVENT_RESIZE = 25,
};

/** @brief XLib event mask */
enum e_evmask
{
	MASK_NONE = (0L),
	MASK_KEY_PRESS = (1L<<0),
	MASK_KEY_RELEASE = (1L<<1),
	MASK_BUTTON_PRESS = (1L<<2),
	MASK_BUTTON_RELEASE = (1L<<3),
	MASK_EnterWindowMask = (1L<<4),
	MASK_LEAVE_WINDOW = (1L<<5),
	MASK_POINTER_MOTION = (1L<<6),
	MASK_PointerMotionHintMask = (1L<<7),
	MASK_Button1MotionMask = (1L<<8),
	MASK_Button2MotionMask = (1L<<9),
	MASK_Button3MotionMask = (1L<<10),
	MASK_Button4MotionMask = (1L<<11),
	MASK_Button5MotionMask = (1L<<12),
	MASK_ButtonMotionMask = (1L<<13),
	MASK_KeymapStateMask = (1L<<14),
	MASK_ExposureMask = (1L<<15),
	MASK_VisibilityChangeMask = (1L<<16),
	MASK_StructureNotifyMask = (1L<<17),
	MASK_ResizeRedirectMask = (1L<<18),
	MASK_SubstructureNotifyMask = (1L<<19),
	MASK_SubstructureRedirectMask = (1L<<20),
	MASK_FocusChangeMask = (1L<<21),
	MASK_PropertyChangeMask = (1L<<22),
	MASK_ColormapChangeMask = (1L<<23),
	MASK_OwnerGrabButtonMask = (1L<<24),
};

/** @} */

////////////////////////////////////////////////////////////////////////////////
// UI Handling                                                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the UI
 *
 * This will setup the MLX handlers, the event handler and the
 * frame loop function.
 *
 * @param app Application pointer
 * @return `true` on success, `false` on errors
 */
bool
ui_setup(struct s_app *app);
/**
 * @brief Cleanup the UI
 *
 * @param app Application pointer
 */
void
ui_cleanup(struct s_app *app);

////////////////////////////////////////////////////////////////////////////////
// Event Handling                                                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup Event Event Handling
 * @ingroup UI
 * @{
 */

/**
 * @brief Event code
 *
 * First byte encodes a @ref e_event_type
 * Next 4 bytes encode the event @ref e_keycode / @ref e_mousecode code
 */
typedef uintptr_t	t_event_code;

/** @brief Types of events */
enum e_event_type
{
	EV_TYPE_MOUSE,
	EV_TYPE_KEY,
};

/** @brief Status of an event */
enum e_event_status
{
	/** @brief Not being used */
	EV_STATUS_INACTIVE,
	/** @brief Key/Button is being held for the first frame */
	EV_STATUS_HELD_FIRST,
	/** @brief Key/Button is being held */
	EV_STATUS_HELD,
	/** @brief Key/Button has been released */
	EV_STATUS_RELEASED
};

/**
 * @brief Setup event handlers
 *
 * @param app Application pointer
 */
void
event_setup(struct s_app *app);
/**
 * @brief Cleanup event handlers
 *
 * @param app Application pointer
 */
void
event_cleanup(struct s_app *app);
/**
 * @brief Function to call at the end of every frames to mark released keys as
 * no longer active
 *
 * @param app Application pointer
 */
void
event_update(struct s_app *app);

/**
 * @brief Check if a @ref e_keycode is being pressed
 *
 * @param app Application pointer
 * @param code Keycode to check
 * @return `true` if key @p code is being pressed, `false` otherwise
 */
bool
ui_key_held(struct s_app *app, enum e_keycode code);
/**
 * @brief Check if a @ref e_keycode is being held down for the first frame
 *
 * @param app Application pointer
 * @param code Keycode to check
 * @return `true` if key @p code is being held down for the first time, `false`
 * otherwise
 */
bool
ui_key_pressed(struct s_app *app, enum e_keycode code);
/**
 * @brief Check if a @ref e_keycode has been pressed (held then released)
 *
 * @param app Application pointer
 * @param code Keycode to check
 * @return `true` if key @p code has been pressed, `false` otherwise
 */
bool
ui_key_released(struct s_app *app, enum e_keycode code);
/**
 * @brief Check if a @ref e_mousecode is being pressed
 *
 * @param app Application pointer
 * @param code Mouse button to check
 * @return `true` if button @p code is being pressed, `false` otherwise
 */
bool
ui_mouse_held(struct s_app *app, enum e_keycode code);
/**
 * @brief Check if a @ref e_mousecode has been pressed (held then released)
 *
 * @param app Application pointer
 * @param code Mouse button to check
 * @return `true` if button @p code has been pressed, `false` otherwise
 */
bool
ui_mouse_pressed(struct s_app *app, enum e_keycode code);

/**
 * @brief Encode an event code from an event type and a @ref e_keycode /
 * @ref e_mousecode code
 *
 * @param type Type of event
 * @param code Code of the event (key/button)
 * @return The event code
 */
t_event_code
encode_event_code(enum e_event_type type, uint32_t code);
/**
 * @brief Decode an event code into an event type and a @ref e_keycode /
 * @ref e_mousecode code
 *
 * @param event Event to decode
 * @param code Resulting key/button
 * @returns The event type
 */
enum e_event_type
decode_event_code(t_event_code event, uint32_t *code);

/** @brief Event data */
typedef struct s_event
{
	/** @brief Current events */
	t_rbtree	events;
	/** @brief Mouse pixel position */
	t_pos		mouse_pos;
	/** @brief Mouse delta from last frame */
	t_pos		mouse_delta;
	/** @brief Lock mouse to screen's center */
	bool		locked_mouse;
}	t_event;

/**
 * @brief Event handler for keyboard releases
 *
 * @param code Released key
 * @param app Application pointer
 */
int
ui_ev_keyup(enum e_keycode code, struct s_app *app);
/**
 * @brief Event handler for keyboard presses
 *
 * @param code Pressed key
 * @param app Application pointer
 */
int
ui_ev_keydown(enum e_keycode code, struct s_app *app);
/**
 * @brief Event handler for mouse relases
 *
 * @param code Released button
 * @param x Mouse X coordinate
 * @param y Mouse Y coordinate
 * @param app Application pointer
 */
int
ui_ev_mouseup(enum e_mousecode code, int x, int y, struct s_app *app);
/**
 * @brief Event handler for mouse presses
 *
 * @param code Pressed button
 * @param x Mouse X coordinate
 * @param y Mouse Y coordinate
 * @param app Application pointer
 */
int
ui_ev_mousedown(enum e_mousecode code, int x, int y, struct s_app *app);
/**
 * @brief Event handler for mouse movements
 *
 * @param x Mouse X coordinate
 * @param y Mouse Y coordinate
 * @param app Application pointer
 */
int
ui_ev_mousemove(int x, int y, struct s_app *app);

/** @} */

/** @} */

#endif // UI_H
