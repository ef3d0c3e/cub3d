/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <map/map.h>

void
	map_free(void *mlx_ptr, t_map *map)
{
	printf("map free: %p\n",mlx_ptr);
	free(map->map);
	atlas_mat_free(&map->material_atlas);
	atlas_tex_free(mlx_ptr, &map->texture_atlas);
}

void
	map_error(t_err_str errstr)
{
	t_err_str	msg;

	msg = err_style(err(err_style(err_style(0, " ERROR: ", (t_text_style){
						COL_WHITE, COL_RED, STYLE_BOLD}), "\n", (t_text_style)
				{0, 0, 0}), errstr), "\n", (t_text_style){0, 0, 0});
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}

bool
	map_asset_load(void *mlx_ptr, t_map *map)
{
	t_atlas_id	id;
	t_texture	*tex;
	int			fd;

	id = 0;
	while (id < map->texture_atlas.size)
	{
		tex = &map->texture_atlas.textures[id];
		fd = open(tex->path, O_RDONLY);
		if (fd == -1)
			return (map_error(err_style(err_style(err(0, "Failed to open textur"
								"e '"), tex->path, (t_text_style){COL_GREEN, 0,
							STYLE_UNDERLINE}), "'", (t_text_style){0, 0, 0})),
					false);
		tex->img = mlx_xpm_file_to_image(mlx_ptr, tex->path,
				&tex->width, &tex->height);
		if (!tex->img)
			return (map_error(err_style(err_style(err(0, "Invalid texture '"),
								tex->path, (t_text_style){COL_GREEN, 0,
							STYLE_UNDERLINE}), "'", (t_text_style){0, 0, 0})),
					false);
		++id;
	}
	return (true);
}
