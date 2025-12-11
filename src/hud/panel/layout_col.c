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
	const t_vec2		cursor = pan_cursor();
	const t_pan_layout	*layout;

	if (ctx->layout_stack_size == 0)
		return ((t_bbox){cursor, (t_vec2){1.f - cursor.x, 1.f - cursor.y}});
	layout = &ctx->layout_stack[ctx->layout_stack_size - 1];
	if (layout->type == LAYOUT_COLUMNS)
		return ((t_bbox){(t_vec2){
			layout->rect.pos.x + layout->rect.size.x, layout->rect.pos.y},
			layout->rect.size
		});
	return (layout->rect);
}

void
	pan_push_columns(const char *id, int n)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);
	t_pan_layout		layout;

	if (ctx->layout_stack_size == PAN_ID_SIZE || !n)
		exit((printf("Invalid pan_push_columns()\n"), 1));
	ft_memset(&layout, 0, sizeof(layout));
	pan_id_push(pan_id_str(id));
	layout.col_count = n;
	layout.col_id = 0;
	layout.rect = available_space();
	layout.rect.size.x /= (float)n;
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
		exit((printf("Invalid pan_next_columns()\n"), 1));
	layout->vertical_space = maxf(layout->vertical_space,
			pan_cursor().y - layout->rect.pos.y);
	pan_id_pop();
	++layout->col_id;
	pan_id_push(pan_id_int(layout->col_id));
	layout->rect = available_space();
	pan_cursor_set(layout->rect.pos);
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
			pan_cursor().y - layout->rect.pos.y);
	pan_id_pop();
	pan_id_pop();
	--ctx->layout_stack_size;
	pan_cursor_set((t_vec2){0, 0});
	if (ctx->layout_stack_size)
		pan_cursor_set(ctx->layout_stack[ctx->layout_stack_size - 1].rect.pos);
	pan_cursor_advance((t_vec2){0, layout->vertical_space});
}
