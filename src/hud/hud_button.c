/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	hud_button_d(const t_drawable *drawable)
{
	t_hud_ctx *const	ctx = hud_context(NULL);
	const t_vec2		size = hud_drawable_size(ctx->app, drawable);
	t_draw_item			rect;

	rect.type = DRAW_RECT_RADIUS;
	rect.draw.rect_radius.radius = ctx->st_button.radius;
	rect.draw.rect_radius.color = ctx->st_button.button_color;
	rect.draw.rect_radius.size = (t_vec2){.4, .4};
	rect.draw.rect_radius.pos = ctx->cursor;
	rect.draw.rect_radius.pos.x += .1f;
	rect.draw.rect_radius.pos.y += .1f;

	hud_draw(ctx->app, rect);
	//hud_drawable_draw(ctx->app, drawable, ctx->cursor);
	return (false);
}

bool
	hud_button(const char *text)
{
	t_hud_ctx *const	ctx = hud_context(NULL);
	const t_draw_item	item = {
		.type = DRAW_TEXT,
		.draw.text = {
		.text = text,
		.font = ctx->font,
		.pos = ctx->cursor
	}};
	const t_drawable	drawable = {
		.items = &item,
		.nitems = 1
	};

	return (hud_button_d(&drawable));
}
