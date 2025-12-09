/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_draw_sprite(t_app *app, const t_sprite *spr, t_draw_params p)
{
	t_color *const	fb = (t_color *)app->framebuffer->data;
	const t_pos		screen0 = (t_pos){(int)((float)app->sizes.x * p.origin.x
			- (float)spr->width * .5f * p.scale.x), (int)((float)app->sizes.y
			* p.origin.y - (float)spr->height * .5f * p.scale.y)};
	t_color			color;
	t_pos			uv;
	t_pos			screen;

	uv.y = 0;
	while ((float)uv.y < (float)spr->height * p.scale.y)
	{
		uv.x = 0;
		while ((float)uv.x < (float)spr->width * p.scale.x)
		{
			color = sprite_sample(spr, (float)uv.x / (((float)spr->width - 1.f)
						* p.scale.x), (float)uv.y / (((float)spr->height - 1.f)
						* p.scale.y));
			screen = (t_pos){screen0.x + uv.x++, screen0.y + uv.y};
			if (color == (t_color)COLOR_UNINIT || screen.x < 0 || screen.x
				>= app->sizes.x || screen.y < 0 || screen.y >= app->sizes.y)
				continue ;
			fb[screen.x + screen.y * app->sizes.x] = color_tint(color, p.color);
		}
		++uv.y;
	}
}

void
	hud_draw_sprite_bilinear(t_app *app, const t_sprite *spr, t_draw_params p)
{
	t_color *const	fb = (t_color *)app->framebuffer->data;
	const t_pos		screen0 = (t_pos){(int)((float)app->sizes.x * p.origin.x
			- (float)spr->width * .5f * p.scale.x), (int)((float)app->sizes.y
			* p.origin.y - (float)spr->height * .5f * p.scale.y)};
	t_color			color;
	t_pos			uv;
	t_pos			screen;

	uv.y = 0;
	while ((float)uv.y < (float)spr->height * p.scale.y)
	{
		uv.x = 0;
		while ((float)uv.x < (float)spr->width * p.scale.x)
		{
			color = sprite_sample_bilinear(spr, (float)uv.x / ((float)spr->width
						* p.scale.x - 1.f), (float)uv.y / ((float)spr->height
						* p.scale.y - 1.f));
			screen = (t_pos){screen0.x + uv.x++, screen0.y + uv.y};
			if (color == (t_color)COLOR_UNINIT || screen.x < 0 || screen.x
				>= app->sizes.x || screen.y < 0 || screen.y >= app->sizes.y)
				continue ;
			fb[screen.x + screen.y * app->sizes.x] = color_tint(color, p.color);
		}
		++uv.y;
	}
}

void
	hud_draw_sprite_item(t_app *app, const t_draw_item *item)
{
	t_draw_params	p;

	p.color = item->draw.sprite.color;
	p.scale = item->draw.sprite.scale;
	p.origin = item->draw.sprite.pos;
	hud_draw_sprite(app, &item->draw.sprite.sprite, p);
}
