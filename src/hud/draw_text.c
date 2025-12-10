/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_draw_text(t_app *app, const t_draw_item *item)
{
	const t_font	*font = &item->draw.text.font;
	size_t			i;
	t_draw_params	p;
	t_sprite		sprite;

	i = 0;
	p.color = font->color;
	p.scale = font->scale;
	p.origin = (t_vec2){item->draw.text.pos.x - .5f * (font_textsize(app, font,
				item->draw.text.text).x - (float)font->base_size.x
			/ (float)app->sizes.x * font->scale.x), item->draw.text.pos.y};
	while (item->draw.text.text[i])
	{
		sprite = font_get(font, item->draw.text.text[i]);
		hud_draw_sprite(app, &sprite, p);
		p.origin.x += (float)font->base_size.x * font->scale.x
			/ (float)app->sizes.x;
		++i;
	}
}

void
	hud_draw_text_shadow(t_app *app, const t_draw_item *item)
{
	const t_font	*font = &item->draw.text_shadow.font;
	size_t			i;
	t_draw_params	p[2];
	t_sprite		sprite;

	i = 0;
	p[0].color = font->color;
	p[0].scale = font->scale;
	p[0].origin = (t_vec2){item->draw.text.pos.x - .5f * (font_textsize(app,
				font, item->draw.text.text).x - (float)font->base_size.x
			/ (float)app->sizes.x * font->scale.x), item->draw.text.pos.y};
	p[1] = p[0];
	p[1].color = item->draw.text_shadow.color_shadow;
	p[1].origin.x += .12f * (float)font->size.x / (float)app->sizes.x;
	p[1].origin.y += .12f * (float)font->size.y / (float)app->sizes.y;
	while (item->draw.text_shadow.text[i])
	{
		sprite = font_get(font, item->draw.text_shadow.text[i++]);
		hud_draw_sprite(app, &sprite, p[1]);
		hud_draw_sprite(app, &sprite, p[0]);
		p[0].origin.x += (float)font->base_size.x * font->scale.x
			/ (float)app->sizes.x;
		p[1].origin.x += (float)font->base_size.x * font->scale.x
			/ (float)app->sizes.x;
	}
}

void
	hud_text(t_app *app, t_pos pos, const char *text, float s)
{
	const t_font		font = font_new(&app->hud.font, 0xFFFFFF, s);
	const t_draw_item	item = font_text(font, (t_vec2){
			(float)pos.x / (float)app->sizes.x,
			(float)pos.y / (float)app->sizes.y
		}, text);

	hud_draw_text(app, &item);
}
