/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

char
	*pan_slider_allocate(const char buf[64])
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (!ctx->slider_arena_offset)
		ft_memcpy(ctx->slider_arena[ctx->slider_arena_offset++], "", 2);
	if (ctx->slider_arena_offset == PAN_SLIDER_ARENA_SIZE)
		return (ctx->slider_arena[0]);
	ft_memcpy(ctx->slider_arena[ctx->slider_arena_offset], buf, 64);
	return (ctx->slider_arena[ctx->slider_arena_offset++]);
}
