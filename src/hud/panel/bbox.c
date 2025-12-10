/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_bbox
	pan_bbox(t_vec2 pos, t_vec2 size, int *padding, int border)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	if (!padding)
	{
		return ((t_bbox){
			pos,
			(t_vec2){
				size.x + 2.f * (float)border / (float)ctx->app->sizes.x,
				size.y + 2.f * (float)border / (float)ctx->app->sizes.y,
			}
		});
	}
	return ((t_bbox){
		pos,
		(t_vec2){
		size.x + (float)(padding[0] + padding[2] + 2 * border)
			/ (float)ctx->app->sizes.x,
		size.y + (float)(padding[1] + padding[3] + 2 * border)
			/ (float)ctx->app->sizes.y,
		}
	});
}

t_vec2
	pan_bbox_center(const t_bbox *bbox)
{
	return ((t_vec2){
		bbox->pos.x + bbox->size.x / 2.f,
		bbox->pos.y + bbox->size.y / 2.f,
	});
}

void
	pan_bbox_screen(const t_bbox *bbox, t_pos *screen_pos, t_pos *screen_size)
{
	t_panel_ctx *const	ctx = pan_ctx(NULL);

	*screen_pos = (t_pos){
		(int)(bbox->pos.x * (float)ctx->app->sizes.x),
		(int)(bbox->pos.y * (float)ctx->app->sizes.y),
	};
	*screen_size = (t_pos){
		(int)(bbox->size.x * (float)ctx->app->sizes.x),
		(int)(bbox->size.y * (float)ctx->app->sizes.y),
	};
}
