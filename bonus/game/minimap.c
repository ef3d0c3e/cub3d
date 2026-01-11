/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

/** @brief Fill the map texture */
static inline void
	minimap_pixels(const t_app *app, t_texture *tex)
{
	t_pos				t;
	t_color				color;
	const t_material	*mat;

	t.y = 0;
	while (t.y < tex->height)
	{
		t.x = 0;
		while (t.x < tex->width)
		{
			mat = map_get(app, t.x, t.y);
			color = 0xFF000000;
			if (!mat)
				color = 0x000000;
			else if (mat->type == MAT_CUBE)
				color = 0x2F2F2F;
			else if (mat->type == MAT_FLOOR)
				color = 0xAFAFAF;
			else if (mat->type == MAT_DOOR)
				color = 0x4F4FFF;
			((t_color *)app->game.minimap.texture->img->data)
			[t.x++ + t.y * tex->width] = color;
		}
		++t.y;
	}
}

bool
	game_minimap_setup(t_app *app)
{
	t_texture	tex;

	tex.width = app->map.size_x;
	tex.height = app->map.size_y;
	tex.img = mlx_new_image(app->mlx_ptr, tex.width, tex.height);
	if (!tex.img)
		return (false);
	tex.path = NULL;
	app->game.minimap = (t_sprite){
		.texture = atlas_tex_get(&app->texture_atlas,
			atlas_tex_add(&app->texture_atlas, tex)),
		.background = 0x000000,
		.width = tex.width,
		.height = tex.height,
		.left = 0,
		.top = 0,
		.line_size = tex.width
	};
	minimap_pixels(app, &tex);
	return (true);
}

void
	game_minimap_render(t_app *app)
{
	const t_pos	pos = {(int)app->game.player.position.x,
		(int)app->game.player.position.y};
	t_sprite	sprite;
	const float	ratio = (float)app->sizes.x / (float)app->sizes.y;
	const int	map_size = (int)((float)app->sizes.y / 10.f * .15f);

	sprite = app->game.minimap;
	sprite.left = clamp(pos.x - map_size / 2, 0, sprite.width - map_size / 2);
	sprite.top = clamp(pos.y - map_size / 2, 0, sprite.height - map_size / 2);
	sprite.width = clamp(map_size, 0, sprite.width);
	sprite.height = clamp(map_size, 0, sprite.height);
	hud_draw(app, (t_draw_item){
		.type = DRAW_SPRITE,
		.draw.sprite = {.sprite = sprite, .color = 0xFFFFFF,
		.scale = (t_vec2){10.f, 10.f},
		.pos = {.82f + .075f, .05f + .075f * ratio}}});
}
