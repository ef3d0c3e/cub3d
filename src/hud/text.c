/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_texts(t_app *app, t_pos pos, const char *text, float s)
{
	t_draw_item	item;

	item.type = DRAW_TEXT;
	item.draw.text.text = text;
	item.draw.text.scale = s;
	item.draw.text.pos = (t_vec2){
		(float)pos.x / (float)app->sizes.x,
		(float)pos.y / (float)app->sizes.y
	};
	item.draw.text.color = 0xFFFFFF;
	hud_draw_text(app, &item);
}

t_vec2
	hud_textsize(t_app *app, const char *text)
{
	const size_t	len = ft_strlen(text);

	return ((t_vec2){
		(float)len * (float)app->assets.hud_font.width * app->hud.scale,
		(float)app->assets.hud_font.height * app->hud.scale,
	});
}
