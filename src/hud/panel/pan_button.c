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
		.border_color = 0XFF1F1F,
		.border_size = 2,
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

	rect.type = DRAW_RECT_RADIUS;
	rect.draw.rect_radius.radius = ctx->st_button.radius;
	rect.draw.rect_radius.border_size = ctx->st_button.border_size;
	rect.draw.rect_radius.border = ctx->st_button.border_color;
	rect.draw.rect_radius.size = bbox.size;
	rect.draw.rect_radius.pos = ctx->cursor;
	rect.draw.rect_radius.color = ctx->st_button.button_color;
	if (hovered)
		rect.draw.rect_radius.color = ctx->st_button.button_color_hover;
	if (hovered && ui_mouse_pressed(ctx->app, MOUSE_LEFT))
		ctx->active = ctx->id_stack[ctx->id_stack_depth];
	if (pan_is_active())
		rect.draw.rect_radius.color = ctx->st_button.button_color_active;
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
	const t_font		font = font_new(&ctx->font, 0x7f7fFF, 1.f);
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

	ctx->cursor = (t_vec2){.1f, .1f};
	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	val = button_draw(&drawable);
	return (val);
}
