/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

inline t_hud_ctx
	*hud_context(t_hud_ctx *ctx)
{
	static t_hud_ctx	g_ctx;

	if (ctx)
		g_ctx = *ctx;
	return (&g_ctx);
}

void
	hud_context_reset(t_app *app)
{
	t_hud_ctx	ctx;

	ctx.font = app->hud.font;
	ctx.scale = (t_vec2){app->hud.scale, app->hud.scale};
	ctx.app = app;
	ctx.cursor = (t_vec2){0, 0};
	hud_context(&ctx);
}
