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

void
	pan_init(t_app *app)
{
	t_panel_ctx	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.font = app->hud.font;
	ctx.scale = (t_vec2){app->hud.scale, app->hud.scale};
	ctx.app = app;
	ctx.cursor = (t_vec2){0, 0};
	ft_memset(ctx.id_stack, 1, sizeof(t_pan_id) * PAN_ID_SIZE);
	ctx.id_stack_depth = 0;
	ctx.st_button = pan_button_style();
	pan_ctx(&ctx);
}

inline t_panel_ctx
	*pan_ctx(t_panel_ctx *ctx)
{
	static t_panel_ctx	g_ctx;

	if (ctx)
		g_ctx = *ctx;
	return (&g_ctx);
}

void
	pan_context_reset(t_app *app)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	ctx->font = app->hud.font;
	ctx->scale = (t_vec2){app->hud.scale, app->hud.scale};
	ctx->app = app;
	ctx->cursor = (t_vec2){0, 0};
	if (ui_mouse_released(ctx->app, MOUSE_LEFT))
		ctx->active = 0;
	ft_memset(ctx->id_stack, 1, sizeof(t_pan_id) * PAN_ID_SIZE);
	ctx->id_stack_depth = 0;
}
