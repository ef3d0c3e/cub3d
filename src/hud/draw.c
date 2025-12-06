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
	const	t_pos	screen = (t_pos){
		(int)((float)app->sizes.x * origin.x - (float)spr->width * .5f * scale.x),
		(int)((float)app->sizes.y * origin.y - (float)spr->height * .5f * scale.y)
	};
	t_color			color;
	t_pos			uv;

	uv.y = 0;
	while ((float)uv.y < (float)app->sizes.y * scale.y)
	{
		uv.x = 0;
		while ((float)uv.x < (float)app->sizes.x * scale.x)
		{
			color = sprite_sample(spr,
					(float)uv.x / ((float)spr->width * scale.x),
					(float)uv.y / ((float)spr->height * scale.y));
			if (color != (t_color)COLOR_UNINIT)
				fb[(screen.x + uv.x) + (screen.y + uv.y) * app->sizes.x] = color;
			++uv.x;
		}
		++uv.y;
	}
}
