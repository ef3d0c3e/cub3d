/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_vec2
	pan_cursor(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (ctx->same_line)
		return (ctx->cursor);
	return (ctx->next_cursor);
}

void
	pan_sameline(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	ctx->same_line = true;
}

void
	pan_cursor_advance(t_vec2 off)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (!ctx->same_line)
	{
		ctx->cursor = ctx->next_cursor;
		ctx->next_cursor.y += off.y;
	}
	ctx->cursor.x += off.x;
	ctx->same_line = false;
}

void
	pan_cursor_advance_m(t_vec2 off)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	off.y += ctx->margin;
	if (!ctx->same_line)
	{
		ctx->cursor = ctx->next_cursor;
		ctx->next_cursor.y += off.y;
	}
	ctx->cursor.x += off.x;
	ctx->same_line = false;
}

void
	pan_cursor_set(t_vec2 pos)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	ctx->cursor = pos;
	ctx->next_cursor = pos;
	ctx->same_line = false;
}
