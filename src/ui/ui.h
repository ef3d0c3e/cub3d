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

/**
 * @defgroup UI UI
 * @{
 */

////////////////////////////////////////////////////////////////////////////////
// MLX wrapper                                                                //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup MLX MLX wrapper
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
 * Next 4 bytes encode the event @ref e_keycode/@ref e_mousecode code
 */
typedef uintptr_t	t_event_code;

/** @brief Types of events */
enum e_event_type
{
	EV_MOUSE_DOWN,
	EV_MOUSE_UP,
	EV_MOUSE_MOVE,
	EV_KEY_DOWN,
	EV_KEY_UP,
};

/**
 * @brief Encode an event code from an event type and a key/button code
 *
 * @param type Type of event
 * @param code Code of the event (key/button)
 * @return The event code
 */
t_event_code
encode_event_code(enum e_event_type type, uint32_t code);
/**
 * @brief Decode an event code into an event type and a key/button code
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
	t_vec2		mouse_pos;
	/** @brief Mouse delta from last frame */
	t_vec2		mouse_delta;
}	t_event;

/** @} */

/** @} */

#endif // UI_H
