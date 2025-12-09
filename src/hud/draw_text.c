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
	p.origin = (t_vec2){item->draw.text.pos.x - .5f * (float)font->base_size.x
		* font->scale.x / (float)app->sizes.x, item->draw.text.pos.y};
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
	t_draw_params	p1;
	t_draw_params	p2;
	t_sprite		sprite;

	i = 0;
	p1.color = font->color;
	p1.scale = font->scale;
	p1.origin = (t_vec2){item->draw.text.pos.x - .5f * (float)font->base_size.x
		* font->scale.x / (float)app->sizes.x, item->draw.text.pos.y};
	p2 = p1;
	p2.color = item->draw.text_shadow.color_shadow;
	p2.origin.x += .12f * (float)font->size.x / (float)app->sizes.x;
	p2.origin.y += .12f * (float)font->size.y / (float)app->sizes.y;
	while (item->draw.text_shadow.text[i])
	{
		sprite = font_get(font, item->draw.text_shadow.text[i++]);
		hud_draw_sprite(app, &sprite, p2);
		hud_draw_sprite(app, &sprite, p1);
		p1.origin.x += (float)font->base_size.x * font->scale.x
			/ (float)app->sizes.x;
		p2.origin.x += (float)font->base_size.x * font->scale.x
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
