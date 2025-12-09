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

t_hud_style_button
	pan_button_style(void)
{
	static const t_hud_style_button	style = (t_hud_style_button){
		.padding = {2, 4, 2, 4},
		.radius = 16,
		.button_color = 0x134CAA,
		.button_color_hover = 0x0000FF,
		.button_color_active = 0x00FF00,
	};

	
	return (style);
}

static bool
	button_draw(const t_drawable *drawable)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_vec2		size = pan_drawable_size(ctx->app, drawable);
	t_draw_item			rect;

	ctx->cursor = (t_vec2){.1, .1};
	rect.type = DRAW_RECT_RADIUS;
	rect.draw.rect_radius.radius = 0 * ctx->st_button.radius;
	rect.draw.rect_radius.color = ctx->st_button.button_color;
	if (pan_mouse_hovered(ctx->app, ctx->cursor, (t_vec2){ctx->cursor.x + size.x, ctx->cursor.y + size.y}))
	{
		rect.draw.rect_radius.color = ctx->st_button.button_color_hover;
		if (ui_mouse_pressed(ctx->app, MOUSE_LEFT))
			ctx->active = ctx->id_stack[ctx->id_stack_depth];
	}
	if (ctx->active == ctx->id_stack[ctx->id_stack_depth])
		rect.draw.rect_radius.color = ctx->st_button.button_color_active;
	rect.draw.rect_radius.size = size;
	rect.draw.rect_radius.pos = ctx->cursor;

	hud_draw(ctx->app, rect);
	pan_drawable_draw(ctx->app, drawable, (t_vec2){
		ctx->cursor.x + size.y / 2,
		ctx->cursor.y + size.y / 2,
	});
	ctx->cursor.y += size.y;
	return (false);
}

bool
	pan_button(const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_font		font = font_new(&ctx->font, 0x7f7fFF, 1.f);
	const t_draw_item	item = {
		.type = DRAW_TEXT,
		.draw.text = {
		.text = text,
		.font = font,
		.pos = ctx->cursor
	}};
	const t_drawable	drawable = {
		.items = &item,
		.nitems = 1
	};
	bool				val;

	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	val = button_draw(&drawable);
	return (val);
}
