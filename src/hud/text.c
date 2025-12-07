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

static void
	glyph_blit(t_app *app, t_pos pos, int glyph, float scale)
{
	const t_sprite	sprite = sprite_sheet_get(&app->assets.hud_font,
			glyph % 16, glyph / 16);
	hud_blit(app, &sprite, (t_vec2){
		(float)pos.x / (float)app->sizes.x,
		(float)pos.y / (float)app->sizes.y
	}, (t_vec2){app->hud.scale * scale, app->hud.scale * scale});
}

void
	hud_text(t_app *app, t_pos pos, const char *text)
{
	size_t	i;

	i = 0;
	while (text[i])
	{
		glyph_blit(app, pos, text[i], 1.f);
		pos.x += (int)((float)app->assets.hud_font.width * app->hud.scale);
		++i;
	}
}

void
	hud_texts(t_app *app, t_pos pos, const char *text, float s)
{
	size_t	i;

	i = 0;
	while (text[i])
	{
		glyph_blit(app, pos, text[i], s);
		pos.x += (int)((float)app->assets.hud_font.width * app->hud.scale * s);
		++i;
	}
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
