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
	hud_menu_move(const char ***items, t_pos *selected, t_pos move)
{
	int	nrow;
	int	ncol;

	nrow = 0;
	while (items[nrow])
		++nrow;
	selected->y += move.y;
	if (selected->y < 0)
		selected->y = 0;
	if (selected->y >= nrow)
		selected->y = nrow - 1;
	ncol = 0;
	while (items[selected->y][ncol])
		++ncol;
	selected->x += move.x;
	if (selected->x < 0)
		selected->x = 0;
	if (selected->x >= ncol)
		selected->x = ncol - 1;
}

void
	hud_menu(t_app *app, const char ***items, t_pos selected)
{
	const t_font	fonts[3] = {
		font_new(&app->hud.font, 0xAFAFAF, 0.2f),
		font_new(&app->hud.font, 0xFFFFFF, 0.2f),
		font_new(&app->hud.font, 0x7F7FFF, 0.2f)
	};
	size_t			nrow;
	t_pos			pos;
	t_vec2			tex;
	int				font_id;

	tex = (t_vec2){(.51f * (float)fonts[0].size.x / (float)app->sizes.x), 0};
	nrow = 0;
	while (items[nrow])
		++nrow;
	pos.y = 0;
	while (items[pos.y])
	{
		pos.x = 0;
		tex.y = (.51f * (float)fonts[0].size.y / (float)app->sizes.y);
		while (items[pos.y][pos.x])
		{
			font_id = 0;
			if (pos.x == selected.x && pos.y == selected.y)
				font_id = 2;
			hud_draw(app, font_text_shadow(fonts[font_id], tex,
					items[pos.y][pos.x], 0x1F1F1F));
			tex.y += (float)fonts[0].size.y / (float)app->sizes.y;
			++pos.x;
		}
		tex.x += 192.f / (float)app->sizes.x;
		++pos.y;
	}
}
