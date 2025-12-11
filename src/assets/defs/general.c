/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	asset_loader_font(t_app *app, t_assets *assets)
{
	(void)assets;

	atlas_tex_load(app->mlx_ptr, &app->texture_atlas, "assets/font.xpm",
		&app->hud.font.texture);
	if (!app->hud.font.texture)
		return (false);
	app->hud.font.scale = (t_vec2){1.f, 1.f};
	app->hud.font.color = (t_color)0xFFFFFF;
	app->hud.font.geom = (t_pos){16, 16};
	app->hud.font.base_size = (t_pos){768 / 16, 768 / 16};
	app->hud.font.size = app->hud.font.base_size;
	return (asset_size_check(app->hud.font.texture, 768, 768));
}

bool
	asset_loader_map(t_app *app, t_assets *assets)
{
	t_atlas_id	id;
	t_texture	*tex;
	int			fd;

	(void)assets;
	id = 0;
	while (id < app->texture_atlas.size)
	{
		tex = &app->texture_atlas.textures[id];
		fd = open(tex->path, O_RDONLY);
		if (fd == -1)
			return (assets_error(tex->path, err(0, "Failed to open file")),
				false);
		close(fd);
		tex->img = mlx_xpm_file_to_image(app->mlx_ptr, tex->path,
				&tex->width, &tex->height);
		if (!tex->img)
			return (assets_error(tex->path, err(0, "Invalid texture")), false);
		++id;
	}
	return (true);
}

bool
	asset_loader_items(t_app *app, t_assets *assets)
{
	atlas_tex_load(app->mlx_ptr, &app->texture_atlas, "assets/items.xpm",
		&assets->items);
	if (!assets->items)
		return (false);
	return (asset_size_check(assets->items, 597, 229));
}
