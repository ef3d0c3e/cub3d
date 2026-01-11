/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

bool
	pan_mouse_hovered(const t_bbox *bbox)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_pos				pos;
	t_pos				size;

	pan_bbox_screen(bbox, &pos, &size);
	if (ctx->app->event.mouse_pos.x < pos.x
		|| ctx->app->event.mouse_pos.x > pos.x + size.x
		|| ctx->app->event.mouse_pos.y < pos.y
		|| ctx->app->event.mouse_pos.y > pos.y + size.y)
		return (false);
	return (true);
}

bool
	pan_is_active(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	return (ctx->active == ctx->id_stack[ctx->id_stack_depth]);
}
