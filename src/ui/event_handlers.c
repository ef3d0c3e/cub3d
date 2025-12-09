/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers_.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

int
	ui_ev_keyup(enum e_keycode code, t_app *app)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_KEY, code);

	rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_RELEASED);
	return (0);
}

int
	ui_ev_keydown(enum e_keycode code, t_app *app)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_KEY, code);
	const void			*status = rb_find(&app->event.events, (void *)ev);

	if (!status || status == (void *)EV_STATUS_INACTIVE)
		rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_HELD_FIRST);
	else
		rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_HELD);
	return (0);
}

int
	ui_ev_mouseup(enum e_mousecode code, int x, int y, t_app *app)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_MOUSE, code);

	(void)x;
	(void)y;
	rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_RELEASED);
	return (0);
}

int
	ui_ev_mousedown(enum e_mousecode code, int x, int y, t_app *app)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_MOUSE, code);
	const void			*status = rb_find(&app->event.events, (void *)ev);

	(void)x;
	(void)y;
	if (!status || status == (void *)EV_STATUS_INACTIVE)
		rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_HELD_FIRST);
	else
		rb_insert(&app->event.events, (void *)ev, (void *)EV_STATUS_HELD);
	return (0);
}

int
	ui_ev_mousemove(int x, int y, t_app *app)
{
	static int	v;
	const t_pos	last_pos = app->event.mouse_pos;
	t_pos		delta;

	if (v)
	{
		v = 0;
		return (0);
	}
	delta = (t_pos){
		x - last_pos.x,
		y - last_pos.y,
	};
	app->event.mouse_delta = delta;
	app->event.mouse_pos = (t_pos){x, y};
	if (app->event.locked_mouse && (abs(delta.x) >= 4 || abs(delta.y) >= 4))
	{
		mlx_mouse_move(app->mlx_ptr, app->mlx_window,
			app->sizes.x / 2, app->sizes.y / 2);
		app->event.mouse_pos = (t_pos){app->sizes.x / 2, app->sizes.y / 2};
		v = 1;
	}
	return (0);
}
