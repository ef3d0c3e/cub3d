/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Comparison function for event codes */
static int
	event_code_cmp(const void *lhs, const void *rhs)
{
	const t_event_code	*left = lhs;
	const t_event_code	*right = rhs;

	if (left < right)
		return (-1);
	else if (left > right)
		return (1);
	return (0);
}

void
	event_setup(t_app *app)
{
	app->event.mouse_pos = (t_vec2){0.f, 0.f};
	app->event.mouse_delta = (t_vec2){0.f, 0.f};
	app->event.events = rb_new(event_code_cmp, NULL, NULL);
	mlx_hook(app->mlx_window, EVENT_MOUSEDOWN, MASK_BUTTON_PRESS,
		ui_ev_mousedown, app);
	mlx_hook(app->mlx_window, EVENT_MOUSEUP, MASK_BUTTON_RELEASE,
		ui_ev_mouseup, app);
	mlx_hook(app->mlx_window, EVENT_MOUSEMOVE, MASK_POINTER_MOTION,
		ui_ev_mousemove, app);
	mlx_hook(app->mlx_window, EVENT_KEYDOWN, MASK_KEY_PRESS,
		ui_ev_keydown, app);
	mlx_hook(app->mlx_window, EVENT_KEYUP, MASK_KEY_RELEASE,
		ui_ev_keyup, app);
	//mlx_hook(app->window, EVENT_EXPOSE, MASK_ExposureMask, ev_expose, app);
	mlx_hook(app->mlx_window, EVENT_DESTROY, MASK_NONE,
		mlx_loop_end, app->mlx_ptr);
}

void
	event_cleanup(t_app *app)
{
	rb_free(&app->event.events);
}

/** @brief A function to mark released keys as no longer active */
static void
	update_pressed_keys(size_t depth, t_rbnode *node, void *cookie)
{
	(void)depth;
	(void)cookie;
	if (node->data == (void *)EV_STATUS_RELEASED)
		node->data = (void *)EV_STATUS_INACTIVE;
	else if (node->data == (void *)EV_STATUS_HELD_FIRST)
		node->data = (void *)EV_STATUS_HELD;
}

void
	event_update(t_app *app)
{
	rb_apply(&app->event.events, update_pressed_keys, NULL);
}
