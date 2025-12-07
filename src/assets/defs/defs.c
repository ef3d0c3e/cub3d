/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

void
	assets_error(const char *path, t_err_str errstr)
{
	t_err_str	msg;

	msg = err_style(err(err_style(err_style(err_style(err_style(0, " ERROR: ",
								(t_text_style){COL_WHITE, COL_RED, STYLE_BOLD}),
							"\nFailed to load asset '", (t_text_style){0, 0, 0}
							), path, (t_text_style){COL_GREEN, 0,
						STYLE_UNDERLINE}), "': ", (t_text_style){0, 0, 0}),
				errstr), "\n", (t_text_style){0, 0, 0});
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}

bool
	asset_size_check(const t_texture *tex, int width, int height)
{
	const t_text_style	st_none = (t_text_style){0, 0, 0};
	const t_text_style	st_pos = (t_text_style){COL_RED, 0, STYLE_BOLD};
	t_err_str			msg;
	char				buf[64];

	if (tex->width == width && tex->height == height)
		return (true);
	itoa_buf(buf, width);
	msg = err_style(err(0, "Expected an image with sizes "), "(", st_pos);
	msg = err_style(err_style(msg, buf, st_pos), ", ", st_pos);
	itoa_buf(buf, height);
	msg = err_style(err_style(msg, buf, st_pos), ")", st_pos);
	itoa_buf(buf, tex->width);
	msg = err_style(err_style(msg, ", got ", st_none), "(", st_pos);
	msg = err_style(err_style(msg, buf, st_pos), ", ", st_pos);
	itoa_buf(buf, tex->height);
	msg = err_style(err_style(msg, buf, st_pos), ")", st_pos);
	msg = err_style(msg, "", st_none);
	assets_error(tex->path, msg);
	return (false);
}

bool
	assets_loader_font(t_app *app, t_assets *assets)
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

/** @brief Loader for map assets */
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
	assets_load(t_app *app)
{
	static const t_asset_loader	loaders[] = {
		asset_loader_map,
		assets_loader_font,
		ent_load_assets,
		NULL,
	};
	size_t						i;

	i = 0;
	while (loaders[i])
	{
		if (!loaders[i](app, &app->assets))
			return (false);
		++i;
	}
	return (true);
}
