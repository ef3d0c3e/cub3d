/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pan_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static inline t_bbox
	bbox_text(const t_font *font, const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_vec2		size = font_textsize(ctx->app, font, text);
	const t_bbox		bbox = pan_bbox(pan_cursor(), size, (const int [4]){
			ctx->padding[0], 0, ctx->padding[1], 0});

	return (bbox);
}

void
	pan_text(const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_font		font = ctx->font;
	const t_bbox		bbox = bbox_text(&font, text);
	const t_draw_item	item = {
		.type = DRAW_TEXT,
		.draw.text = {
		.text = text,
		.font = font,
		.pos = pan_bbox_center(&bbox),
	}};

	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	hud_draw(ctx->app, item);
	pan_cursor_advance_m(bbox.size);
}

void
	pan_text_color(const char *text, t_color color)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_font		font = font_new(&ctx->font, color, 1.f);
	const t_bbox		bbox = bbox_text(&font, text);
	const t_draw_item	item = {
		.type = DRAW_TEXT,
		.draw.text = {
		.text = text,
		.font = font,
		.pos = pan_bbox_center(&bbox),
	}};

	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	hud_draw(ctx->app, item);
	pan_cursor_advance_m(bbox.size);
}
