/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Retrieve maximum available space based on the previous layout */
static inline t_bbox
	available_space(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	const t_pan_layout	*layout;
	float				width;

	if (ctx->layout_stack_size == 0)
		return ((t_bbox){(t_vec2){0, 0}, (t_vec2){1, 1}});
	layout = &ctx->layout_stack[ctx->layout_stack_size - 1];
	if (layout->type == LAYOUT_COLUMNS)
	{
		width = layout->rect.size.x / (float)layout->col_count;
		return ((t_bbox){
			(t_vec2){layout->rect.pos.x + width * (float)layout->col_id,
			layout->rect.pos.y
		},
		(t_vec2){width, layout->rect.size.y}
		});
	}
	return (layout->rect);
}

void
	pan_push_columns(const char *id, int n)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_pan_layout		layout;

	if (ctx->layout_stack_size == PAN_ID_SIZE || !n)
	{
		printf("Invalid pan_push_columns()\n");
		return ;
	}
	ft_memset(&layout, 0, sizeof(layout));
	pan_id_push(pan_id_str(id));
	layout.col_count = n;
	layout.col_id = 0;
	layout.rect = available_space();
	layout.type = LAYOUT_COLUMNS;
	ctx->layout_stack[ctx->layout_stack_size++] = layout;
	pan_id_push(pan_id_int(0));
}

void
	pan_next_columns(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_pan_layout *const	layout = &ctx->layout_stack[ctx->layout_stack_size - 1];

	if (!ctx->layout_stack_size || layout->type != LAYOUT_COLUMNS
		|| layout->col_id + 1 == layout->col_count)
	{
		printf("Invalid pan_next_columns()\n");
		return ;
	}
	layout->vertical_space = maxf(layout->vertical_space,
			ctx->cursor.y - layout->rect.pos.y);
	pan_id_pop();
	++layout->col_id;
	pan_id_push(pan_id_int(layout->col_id));
	layout->rect = available_space();
	ctx->cursor = layout->rect.pos;
}

void
	pan_pop_columns(void)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_pan_layout *const	layout = &ctx->layout_stack[ctx->layout_stack_size - 1];

	if (!ctx->layout_stack_size || layout->type != LAYOUT_COLUMNS
		|| layout->col_id + 1 != layout->col_count)
	{
		printf("Invalid pan_pop_columns()\n");
		return ;
	}
	layout->vertical_space = maxf(layout->vertical_space,
			ctx->cursor.y - layout->rect.pos.y);
	pan_id_pop();
	pan_id_pop();
	--ctx->layout_stack_size;
	ctx->cursor = (t_vec2){0, 0};
	if (ctx->layout_stack_size)
		ctx->cursor = ctx->layout_stack[ctx->layout_stack_size - 1].rect.pos;
	ctx->cursor.y += layout->vertical_space;
}
