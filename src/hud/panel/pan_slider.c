/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pan_slider.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static t_bbox
	bbox_slider(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_vec2				text_size;
	const int			pad = maxi(ctx->padding[0], ctx->padding[1]);

	text_size = font_textsize(ctx->app, &ctx->font, "a");
	text_size.x *= (float)ctx->st_slider.base_width;
	return (pan_bbox(pan_cursor(), text_size, (const int [4]){pad, pad, pad,
			pad}, ctx->st_slider.border_size));
}

bool
	slider_logic_i(const t_bbox *bbox, int *v, const int *p)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const int			bounds[2] = {
		(int)(bbox->pos.x * (float)ctx->app->sizes.x),
		(int)((bbox->pos.x + bbox->size.x) * (float)ctx->app->sizes.x)
	};
	const int			pos = clamp(ctx->app->event.mouse_pos.x,
			bounds[0], bounds[1]);
	const int			prev = *v;

	*v = clamp((int)((float)p[0] + ((float)(pos - bounds[0])
					/ (float)(bounds[1] - bounds[0]))
				* ((float)p[1] - (float)p[0])), p[0], p[1]);
	return (*v != prev);
}

bool
	pan_slider_i(const char *text, int *v, const int *p)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_bbox		bbox = bbox_slider();
	const bool			hovered = pan_mouse_hovered(&bbox);
	int					color;
	bool				status;
	char				b[64];

	ctx->id_stack[ctx->id_stack_depth] = pan_id_str(text);
	color = hovered;
	status = false;
	if (pan_is_active())
	{
		color = 2;
		status = slider_logic_i(&bbox, v, p);
	}
	if (hovered && ui_mouse_pressed(ctx->app, MOUSE_LEFT))
		ctx->active = ctx->id_stack[ctx->id_stack_depth];
	sprintf(b, "%d", *v);
	pan_slider_draw(bbox, color, (float)(*v - p[0]) / (float)(p[1] - p[0]), pan_slider_allocate(b));
	pan_sameline();
	pan_text(text);
	return (status);
}
