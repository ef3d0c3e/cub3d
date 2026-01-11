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
	const int	sx = screen_size.x;
	const int	sy = screen_size.y;

	bbox[0].x = clamp((int)(pos.x * (float)sx + .5f), 0, sx);
	bbox[0].y = clamp((int)(pos.y * (float)sy + .5f), 0, sy);
	bbox[1].x = clamp((int)((pos.x + size.x) * (float)sx + .5f), 0, sx);
	bbox[1].y = clamp((int)((pos.y + size.y) * (float)sy + .5f), 0, sy);
}

static inline void
	rect_radius(t_app *app, const t_draw_item *item, t_pos c, const t_pos v[4])
{
	t_color *const	fb = (t_color *)app->framebuffer->data;
	const int		b = item->draw.rect_radius.border_size;
	int				dist2;

	if (v[1].x && v[1].y)
	{
		dist2 = v[1].x * v[1].x + v[1].y * v[1].y;
		if (dist2 > v[2].x)
			return ;
		if (b > 0 && dist2 >= v[2].y)
			fb[c.x + c.y * app->sizes.x] = item->draw.rect_radius.border;
		else
			fb[c.x + c.y * app->sizes.x] = item->draw.rect_radius.color;
	}
	else
	{
		if (b > 0
			&& (v[0].x < b || v[0].x >= v[3].x - b || v[0].y < b
				|| v[0].y >= v[3].y - b))
			fb[c.x + c.y * app->sizes.x] = item->draw.rect_radius.border;
		else
			fb[c.x + c.y * app->sizes.x] = item->draw.rect_radius.color;
	}
}

void
	hud_draw_rect_radius(t_app *app, const t_draw_item *item)
{
	t_pos			bbox[2];
	const int		r = item->draw.rect_radius.radius;
	const int		b = item->draw.rect_radius.border_size;
	t_pos			v[4];

	get_bbox(bbox, app->sizes, item->draw.rect_radius.pos,
		item->draw.rect_radius.size);
	ft_memset(v, 0, sizeof(v));
	v[3] = (t_pos){bbox[1].x - bbox[0].x, bbox[1].y - bbox[0].y};
	v[1].y = (v[0].y < r) * (r - v[0].y)
		+ (v[0].y >= v[3].y - r) * (v[0].y - v[3].y + r + 1);
	v[2] = (t_pos){r * r, maxi((r - b) * (r - b), 0)};
	while (v[0].y < v[3].y)
	{
		v[1].x = (v[0].x < r) * (r - v[0].x)
			+ (v[0].x >= v[3].x - r) * (v[0].x - v[3].x + r + 1);
		rect_radius(app, item, (t_pos){bbox[0].x + v[0].x, bbox[0].y + v[0].y},
			v);
		if (++v[0].x == v[3].x)
		{
			v[1].y = (v[0].y < r) * (r - v[0].y)
				+ (v[0].y >= v[3].y - r) * (v[0].y - v[3].y + r + 1);
			v[0].x = 0 * (++v[0].y);
		}
	}
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
