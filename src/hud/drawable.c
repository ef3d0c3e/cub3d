/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_vec2
	hud_drawable_size(const t_app *app, const t_drawable *drawable)
{
	t_vec2	size;
	t_vec2	total;
	size_t	i;

	i = 0;
	total = (t_vec2){0, 0};
	while (i < drawable->nitems)
	{
		size = draw_item_size(app, &drawable->items[i]);
		total = (t_vec2){maxf(size.x, total.x), maxf(size.y, total.y)};
		++i;
	}
	return (total);
}

void
	hud_drawable_draw(t_app *app, const t_drawable *drawable, t_vec2 offset)
{
	size_t	i;

	i = 0;
	while (i < drawable->nitems)
	{
		hud_draw(app, draw_item_offset(app, drawable->items[i], offset));
		++i;
	}
}
