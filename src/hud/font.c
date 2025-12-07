/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.       c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

t_font
	font_new(const t_font *base, t_color color, float scale)
{
	t_font	new;
	new = *base;
	new.scale.x *= scale;
	new.scale.y *= scale;
	new.color = color;
	new.size = (t_pos){
		(int)((float)base->base_size.x * scale),
		(int)((float)base->base_size.y * scale)
	};
	return (new);
}

t_draw_item
	font_text(t_font font, t_vec2 pos, const char *text)
{
	t_draw_item	item;

	item.type = DRAW_TEXT;
	item.draw.text.text = text;
	item.draw.text.pos = pos;
	item.draw.text.font = font;
	return (item);
}

t_draw_item
	font_text_shadow(
	t_font font,
	t_vec2 pos,
	const char *text,
	t_color color_shadow)
{
	t_draw_item	item;

	item.type = DRAW_TEXT_SHADOW;
	item.draw.text_shadow.text = text;
	item.draw.text_shadow.pos = pos;
	item.draw.text_shadow.font = font;
	item.draw.text_shadow.color_shadow = color_shadow;
	return (item);
}

t_sprite
	font_get(const t_font *font, int ch)
{
	t_sprite	spr;
	const int	x = ch % font->geom.x;
	const int	y = ch / font->geom.x;

	spr.texture = font->texture;
	spr.background = font->background;
	spr.line_size = font->texture->width;
	spr.width = font->base_size.x;
	spr.height = font->base_size.x;
	spr.left = x * font->base_size.x;
	spr.top = y * font->base_size.y;
	return (spr);
}
