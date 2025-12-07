/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	hud_blit(t_app *app, const t_sprite *spr, t_vec2 origin, t_vec2 scale)
{
	t_color *const	fb = (t_color *)app->framebuffer->data;
	const t_pos		screen0 = (t_pos){(int)((float)app->sizes.x * origin.x
			- (float)spr->width * .5f * scale.x), (int)((float)app->sizes.y
			* origin.y - (float)spr->height * .5f * scale.y)};
	t_color			color;
	t_pos			uv;
	t_pos			screen;

	uv.y = 0;
	while ((float)uv.y < (float)spr->height * scale.y)
	{
		uv.x = 0;
		while ((float)uv.x < (float)spr->width * scale.x)
		{
			color = sprite_sample_bilinear(spr, (float)uv.x / ((float)spr->width
						* scale.x), (float)uv.y / ((float)spr->height
						* scale.y));
			screen = (t_pos){screen0.x + uv.x, screen0.y + uv.y};
			if (color != (t_color)COLOR_UNINIT && screen.x >= 0 && screen.x
				< app->sizes.x && screen.y >= 0 && screen.y < app->sizes.y)
				fb[screen.x + screen.y * app->sizes.x] = color;
			++uv.x;
		}
		++uv.y;
	}
}
