/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	ui_key_held(t_app *app, enum e_keycode code)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_KEY, code);
	const void			*status = rb_find(&app->event.events, (void *)ev);

	return (status == (void *)EV_STATUS_HELD
		|| status == (void *)EV_STATUS_HELD_FIRST);
}

bool
	ui_key_pressed(t_app *app, enum e_keycode code)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_KEY, code);

	return (rb_find(&app->event.events, (void *)ev)
		== (void *)EV_STATUS_HELD_FIRST);
}

bool
	ui_key_released(t_app *app, enum e_keycode code)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_KEY, code);

	return (rb_find(&app->event.events, (void *)ev)
		== (void *)EV_STATUS_RELEASED);
}

bool
	ui_mouse_held(t_app *app, enum e_keycode code)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_MOUSE, code);

	return (rb_find(&app->event.events, (void *)ev)
		== (void *)EV_STATUS_HELD);
}

bool
	ui_mouse_pressed(t_app *app, enum e_keycode code)
{
	const t_event_code	ev = encode_event_code(EV_TYPE_MOUSE, code);

	return (rb_find(&app->event.events, (void *)ev)
		== (void *)EV_STATUS_RELEASED);
}
