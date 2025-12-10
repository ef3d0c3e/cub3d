/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pan_checkbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_pan_style_checkbox
	pan_checkbox_style(void)
{
	static const t_pan_style_checkbox	style = (t_pan_style_checkbox){
		.rounding = 4,
		.colors = {
		0x2E2E2E, 0x3A3A3A,
		0x404040, 0x505050,
		0x1F1F1F, 0x3A3A3A
	},
		.border_size = 1,
		.check_color = 0x00FF00,
		.spacing = 4,
	};

	return (style);
}

static t_bbox
	bbox_checkbox(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_vec2		text_size = font_textsize(ctx->app, &ctx->font, "\002");
	const int			pad = maxi(ctx->padding[0], ctx->padding[1]);

	return (pan_bbox(pan_cursor(), text_size, (const int [4]){pad, pad, pad,
			pad}, ctx->st_checkbox.border_size));
}

static void
	checkbox_mark(t_bbox bbox, bool checked, int color)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	hud_draw(ctx->app, (t_draw_item){
		.type = DRAW_RECT_RADIUS,
		.draw.rect_radius = {
		.radius = ctx->st_checkbox.rounding,
		.border_size = ctx->st_checkbox.border_size,
		.color = ctx->st_checkbox.colors[2 * color],
		.border = ctx->st_checkbox.colors[2 * color + 1],
		.pos = pan_cursor(),
		.size = bbox.size,
	}});
	if (checked)
		hud_draw(ctx->app, (t_draw_item){
			.type = DRAW_TEXT,
			.draw.text = {
			.font = font_new(&ctx->font,
				ctx->st_checkbox.check_color, 1.4f),
			.text = "\002",
			.pos = pan_bbox_center(&bbox),
		}});
	bbox.size.x += (float)ctx->st_checkbox.spacing / (float)ctx->app->sizes.x;
	pan_cursor_advance(bbox.size);
}

bool
	pan_checkbox(const char *text, bool *val)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_bbox		bbox = bbox_checkbox();
	const bool			hovered = pan_mouse_hovered(&bbox);
	bool				active;
	int					color;

	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	if (hovered && ui_mouse_pressed(ctx->app, MOUSE_LEFT))
		ctx->active = ctx->id_stack[ctx->id_stack_depth];
	color = hovered;
	active = pan_is_active();
	if (active)
		color = 2;
	checkbox_mark(bbox, *val, color);
	pan_sameline();
	pan_text(text);
	if (ui_mouse_released(ctx->app, MOUSE_LEFT) && active && hovered)
	{
		*val = !*val;
		return (true);
	}
	return (false);
}
