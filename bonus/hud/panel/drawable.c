/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_vec2
	pan_drawable_size(const t_drawable *drawable)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_vec2				size;
	t_vec2				total;
	size_t				i;

	i = 0;
	total = (t_vec2){0, 0};
	while (i < drawable->nitems)
	{
		size = draw_item_size(ctx->app, &drawable->items[i]);
		total = (t_vec2){maxf(size.x, total.x), maxf(size.y, total.y)};
		++i;
	}
	return (total);
}

void
	pan_drawable_draw(const t_drawable *drawable, t_vec2 offset)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	size_t				i;

	i = 0;
	while (i < drawable->nitems)
	{
		hud_draw(ctx->app,
			draw_item_offset(ctx->app, drawable->items[i], offset));
		++i;
	}
}
