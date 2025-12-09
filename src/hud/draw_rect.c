/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

/** @brief Get the rectangle's bounding box scaled to screen */
static inline void
	get_bbox(t_pos bbox[2], t_pos screen_size, t_vec2 pos, t_vec2 size)
{
	bbox[0].x = clamp((int)(pos.x * (float)screen_size.x + .5f),
			0, screen_size.x - 1);
	bbox[0].y = clamp((int)(pos.y * (float)screen_size.y + .5f),
			0, screen_size.y - 1);
	bbox[1].x = clamp((int)((pos.x + size.x) * (float)screen_size.x + .5f),
			0, screen_size.x - 1);
	bbox[1].y = clamp((int)((pos.y + size.y) * (float)screen_size.y + .5f),
			0, screen_size.y - 1);
}

void
	hud_draw_rect(t_app *app, const t_draw_item *item)
{
	t_color *const	fb = (t_color *)app->framebuffer->data;
	t_pos			bbox[2];
	t_pos			c;

	get_bbox(bbox, app->sizes, item->draw.rect.pos, item->draw.rect.size);
	c.y = bbox[0].y;
	while (c.y < bbox[1].y)
	{
		c.x = bbox[0].x;
		while (c.x < bbox[1].x)
		{
			fb[c.x + c.y * app->sizes.x] = item->draw.rect.color;
			++c.x;
		}
		++c.y;
	}
}

void
	hud_draw_rect_radius(t_app *app, const t_draw_item *item)
{
	t_color *const		fb = (t_color *)app->framebuffer->data;
	t_pos				bbox[2];
	const int			radius = item->draw.rect_radius.radius;
	int					radius_factor;
	t_pos				c;

	get_bbox(bbox, app->sizes,
		item->draw.rect_radius.pos, item->draw.rect_radius.size);
	c.y = bbox[0].y;
	while (c.y < bbox[1].y)
	{
		radius_factor = 0;
		if (c.y - bbox[0].y < radius)
			radius_factor = (int)sqrtf((float)(radius * radius
						- (radius - (c.y - bbox[0].y))
						* (radius - (c.y - bbox[0].y))));
		else if (bbox[1].y - c.y <= radius)
			radius_factor = (int)sqrtf((float)(radius * radius
						- (radius - (bbox[1].y - c.y - 1))
						* (radius - (bbox[1].y - c.y - 1))));
		c.x = bbox[0].x + radius_factor;
		while (c.x < bbox[1].x - radius_factor)
			fb[c.x++ + c.y * app->sizes.x] = item->draw.rect_radius.color;
		++c.y;
	}
}
