/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <lgamba@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:54:01 by lgamba            #+#    #+#             */
/*   Updated: 2025/02/18 17:50:12 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_pan_id
	pan_id_str(const char *id)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_pan_id		seed = ctx->id_stack[ctx->id_stack_depth];

	return (murmumr3_32((const void *)id, ft_strlen(id), seed));
}

t_pan_id
	pan_id_int(const int id)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_pan_id		seed = ctx->id_stack[ctx->id_stack_depth];

	return (murmumr3_32((const void *)&id, sizeof(id), seed));
}

void
	pan_id_push(t_pan_id id)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (ctx->id_stack_depth + 1 == PAN_ID_SIZE)
	{
		printf("Panel stack overflow\n");
		return ;
	}
	ctx->id_stack[ctx->id_stack_depth++] = id;
}

void
	pan_id_pop(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (ctx->id_stack_depth == 0)
	{
		printf("Panel stack underflow\n");
		return ;
	}
	--ctx->id_stack_depth;
}
