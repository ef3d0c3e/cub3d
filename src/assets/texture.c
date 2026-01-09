/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "assets/defs/defs.h"
#include <assets/assets.h>

t_atlas_id
	atlas_tex_add(t_texture_atlas *atlas, t_texture texture)
{
	size_t	i;

	i = 0;
	while (texture.path && i < atlas->size)
	{
		if (!ft_strcmp(atlas->textures[i].path, texture.path))
		{
			free(texture.path);
			return ((t_atlas_id)i);
		}
		++i;
	}
	if (atlas->size == atlas->capacity)
	{
		atlas->capacity = atlas->capacity * 2ULL + !atlas->capacity * 16ULL;
		atlas->textures = xrealloc(atlas->textures,
				atlas->size * sizeof(texture),
				atlas->capacity * sizeof(texture));
	}
	atlas->textures[atlas->size++] = texture;
	return ((t_atlas_id)(atlas->size - 1));
}

void
	atlas_tex_free(void *mlx_ptr, t_texture_atlas *atlas)
{
	size_t	i;

	i = 0;
	while (i < atlas->size)
	{
		free(atlas->textures[i].path);
		if (mlx_ptr && atlas->textures[i].img)
			mlx_destroy_image(mlx_ptr, atlas->textures[i].img);
		++i;
	}
	free(atlas->textures);
}

const t_texture
	*atlas_tex_get(const t_texture_atlas *atlas, t_atlas_id tex_id)
{
	if (tex_id >= atlas->size)
		return (NULL);
	return (&atlas->textures[tex_id]);
}

/** @brief Check if texture is already loaded to prevent double-loading */
static inline t_atlas_id
	already_loaded(
	t_texture_atlas *atlas,
	const char *path,
	const t_texture **out)
{
	t_atlas_id	id;

	id = 0;
	while (id < atlas->size)
	{
		if (atlas->textures[id].path && !ft_strcmp(atlas->textures[id].path,
				path))
		{
			if (out)
				*out = &atlas->textures[id];
			return (id);
		}
		++id;
	}
	return ((t_atlas_id)ATLAS_INVALID);
}

t_atlas_id
	atlas_tex_load(
	void *mlx_ptr,
	t_texture_atlas *atlas,
	const char *path,
	const t_texture **out)
{
	t_texture	tex;
	t_atlas_id	id;
	int			fd;

	if (out)
		*out = NULL;
	id = already_loaded(atlas, path, out);
	if (id != (t_atlas_id)ATLAS_INVALID)
		return (id);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (assets_error(path, err(0, " Cannot open file")),
			(t_atlas_id)ATLAS_INVALID);
	close(fd);
	ft_memset(&tex, 0, sizeof(tex));
	tex.path = ft_strdup(path);
	tex.img = mlx_xpm_file_to_image(mlx_ptr, tex.path, &tex.width, &tex.height);
	if (!tex.img)
		return (assets_error(tex.path, err(0, " `mlx_xpm_file_to_image` failed"
				)), free(tex.path), (t_atlas_id)ATLAS_INVALID);
	id = atlas_tex_add(atlas, tex);
	if (out)
		*out = &atlas->textures[id];
	return (id);
}
