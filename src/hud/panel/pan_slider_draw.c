/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pan_slider_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_pan_style_slider
	pan_slider_style(void)
{
	const t_pan_style_slider	style = (t_pan_style_slider){
		.rounding = 1,
		.colors = {
		0x2E2E2E, 0x3A3A3A,
		0x404040, 0x505050,
		0x1F1F1F, 0x3A3A3A},
		.slider = 0x7f7f7f,
		.border_size = 1,
		.spacing = 4,
		.base_width = 8,
		.slider_geom = (t_vec2){.06f, 0.8f},
		.padding = {2, 2},
	};

	return (style);
}

static t_bbox
	bbox_slider_pallet(const t_bbox *bbox, float f)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_vec2		cur = pan_cursor();
	const t_vec2		size = (t_vec2){
		ctx->st_slider.slider_geom.x * bbox->size.x,
		ctx->st_slider.slider_geom.y * bbox->size.y};
	const float			padding[2] = {
		(float)ctx->st_slider.padding[0] / (float)ctx->app->sizes.x,
		(float)ctx->st_slider.padding[1] / (float)ctx->app->sizes.x,
	};
	const t_vec2		pos = (t_vec2){
		cur.x + padding[0] + (f - f * ctx->st_slider.slider_geom.x)
		* (bbox->size.x - padding[0] - padding[1]),
		cur.y + bbox->size.y * .5f * (1.f - ctx->st_slider.slider_geom.y)
	};

	return ((t_bbox){pos, size});
}

void
	pan_slider_draw(t_bbox bbox, int color, float f, const char *text)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_bbox		inner = bbox_slider_pallet(&bbox, f);

	hud_draw(ctx->app, (t_draw_item){.type = DRAW_RECT_RADIUS,
		.draw.rect_radius = {
		.radius = ctx->st_slider.rounding,
		.border_size = ctx->st_slider.border_size,
		.color = ctx->st_slider.colors[2 * color],
		.border = ctx->st_slider.colors[2 * color + 1],
		.pos = pan_cursor(),
		.size = bbox.size}});
	hud_draw(ctx->app, (t_draw_item){.type = DRAW_RECT,
		.draw.rect = {
		.color = ctx->st_slider.slider,
		.pos = inner.pos,
		.size = inner.size}});
	hud_draw(ctx->app, (t_draw_item){.type = DRAW_TEXT,
		.draw.text = {
		.font = ctx->font,
		.text = text,
		.pos = pan_bbox_center(&bbox)}});
	bbox.size.x += (float)ctx->st_checkbox.spacing / (float)ctx->app->sizes.x;
	pan_cursor_advance_m(bbox.size);
}
