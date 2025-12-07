/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_menu(t_app *app, const char ***items, t_pos selected)
{
	const t_font	font = font_new(&app->hud.font, 0xFFFFFF, 1.f);
	size_t			nrow;
	t_draw_item		text;
	t_pos			pos;
	t_vec2			tex;

	printf("font: %d\n", font.geom.x);
	hud_draw(app, font_text(font, (t_vec2){.15f, .5}, "Test"));

	tex = (t_vec2){(.5f * (float)font.base_size.x / (float)app->sizes.x), 0};
	nrow = 0;
	while (items[nrow])
		++nrow;
	pos.y = 0;
	while (items[pos.y])
	{
		pos.x = 0;
		tex.y = (.5f * (float)font.base_size.y / (float)app->sizes.y);
		while (items[pos.y][pos.x])
		{
			printf("px=%d\n",pos.x);
			text = font_text_shadow(font, tex, items[pos.y][pos.x], 0X1F1F1F);
			hud_draw(app, text);
			tex.y += (float)font.base_size.y / (float)app->sizes.y;
			++pos.x;
		}
		tex.x += 256.f / (float)app->sizes.x;
		++pos.y;
	}
}
