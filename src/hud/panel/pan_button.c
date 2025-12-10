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
		.padding = {6, 12, 6, 12},
		.radius = 3,
		.colors = {
			0x2E2E2E, 0x3A3A3A,
			0x404040, 0x505050,
			0x1F1F1F, 0x3A3A3A
		},
		.border_size = 1,
	};
	
	return (style);
}

static bool
	button_draw(const t_drawable *drawable)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_bbox		bbox = pan_bbox(ctx->cursor, pan_drawable_size(drawable
				), ctx->st_button.padding, ctx->st_button.border_size);
	const bool			hovered = pan_mouse_hovered(&bbox);
	t_draw_item			rect;
	int					color;

	rect.type = DRAW_RECT_RADIUS;
	rect.draw.rect_radius.radius = ctx->st_button.radius;
	rect.draw.rect_radius.border_size = ctx->st_button.border_size;
	rect.draw.rect_radius.size = bbox.size;
	rect.draw.rect_radius.pos = ctx->cursor;
	if (hovered && ui_mouse_pressed(ctx->app, MOUSE_LEFT))
		ctx->active = ctx->id_stack[ctx->id_stack_depth];
	color = hovered * !pan_is_active() + 2 * pan_is_active();
	rect.draw.rect_radius.color = ctx->st_button.colors[color * 2];
	rect.draw.rect_radius.border = ctx->st_button.colors[color * 2 + 1];
	hud_draw(ctx->app, rect);
	pan_drawable_draw(drawable, (t_vec2){ctx->cursor.x + bbox.size.x / 2,
		ctx->cursor.y + bbox.size.y / 2,});
	ctx->cursor.y += bbox.size.y;
	return (ui_mouse_released(ctx->app, MOUSE_LEFT) && pan_is_active() && hovered);
}

bool
	pan_button(const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_font		font = font_new(&ctx->font, 0x7F7FFF, .4f);
	const t_draw_item	item = {
		.type = DRAW_TEXT,
		.draw.text = {
		.text = text,
		.font = font,
		.pos = {0.f, 0.f},
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
