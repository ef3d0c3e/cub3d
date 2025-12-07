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
	size_t			i;
	t_draw_params	p;
	t_sprite		sprite;
	const float		scale = item->draw.text.scale * app->hud.scale;

	i = 0;
	p.color = item->draw.text.color;
	p.scale = (t_vec2){scale, scale};
	p.origin = item->draw.text.pos;
	while (item->draw.text.text[i])
	{
		sprite = sprite_sheet_get(&app->assets.hud_font,
				item->draw.text.text[i] % 16, item->draw.text.text[i] / 16);
		hud_draw_sprite(app, &sprite, p);
		p.origin.x += (float)sprite.width * scale / (float)app->sizes.x;
		++i;
	}
}

void
	hud_draw_text_shadow(t_app *app, const t_draw_item *item)
{
	size_t			i;
	t_draw_params	p1;
	t_draw_params	p2;
	t_sprite		sprite;
	const float		scale = item->draw.text_shadow.scale * app->hud.scale;

	i = 0;
	p1.color = item->draw.text_shadow.color;
	p1.scale = (t_vec2){scale, scale};
	p1.origin = item->draw.text_shadow.pos;
	p2 = p1;
	p2.color = item->draw.text_shadow.color_shadow;
	p2.origin.x += 2.f / (float)app->sizes.x;
	p2.origin.y += 2.f / (float)app->sizes.y;
	while (item->draw.text_shadow.text[i])
	{
		sprite = sprite_sheet_get(&app->assets.hud_font,
				item->draw.text_shadow.text[i] % 16,
				item->draw.text_shadow.text[i] / 16);
		hud_draw_sprite(app, &sprite, p2);
		hud_draw_sprite(app, &sprite, p1);
		p1.origin.x += (float)sprite.width * scale / (float)app->sizes.x;
		p2.origin.x += (float)sprite.width * scale / (float)app->sizes.x;
		++i;
	}
}
