/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	action_text(t_app *app, const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	static size_t		last_frame;
	static int			nitems;
	t_vec2				size;
	t_vec2				cursor;

	if (app->frame != last_frame)
	{
		last_frame = app->frame;
		nitems = 0;
	}
	cursor = pan_cursor();
	size = font_textsize(app, &ctx->font, text);
	size.y *= 1.5f;
	pan_cursor_set((t_vec2){.5f - size.x / 2.f, .55f + size.y * (float)nitems});
	++nitems;
	pan_text(text);
	pan_cursor_set(cursor);
}
