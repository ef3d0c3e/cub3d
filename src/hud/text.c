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
	glyph_blit(t_app *app, t_pos pos, int glyph)
{
	//t_color *const	fb = (t_color *)app->framebuffer->data;
	const t_sprite	sprite = sprite_sheet_get(&app->assets.hud_font,
			glyph % 16, glyph / 16);
	hud_blit(app, &sprite, (t_vec2){(float)pos.x / (float)app->sizes.x, (float)pos.y / (float)app->sizes.y}, (t_vec2){.5, .5});
	//t_pos			uv;
	//t_color			color;

	//uv.y = 0;
	//while (uv.y < sprite.height)
	//{
	//	uv.x = 0;
	//	while (uv.x < sprite.width)
	//	{
	//		color = sprite_sample(&sprite, (float)uv.x / (float)sprite.width,
	//				(float)uv.y / (float)sprite.height);
	//		if (color != (t_color)COLOR_UNINIT)
	//			fb[(pos.x + uv.x) + (pos.y + uv.y) * (int)app->sizes.x] = color;
	//		++uv.x;
	//	}
	//	++uv.y;
	//}
}

void
	hud_text(t_app *app, t_pos pos, const char *text)
{
	size_t	i;

	i = 0;
	while (text[i])
	{
		glyph_blit(app, pos, text[i]);
		pos.x += app->assets.hud_font.width / 2;
		++i;
	}
}
