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
#include <assets/assets.h>

t_atlas_id
	atlas_tex_add(t_texture_atlas *atlas, t_texture texture)
{
	if (atlas->size == atlas->capacity)
	{
		atlas->capacity = atlas->capacity * 2 + !atlas->capacity * 16;
		atlas->textures = xrealloc(atlas->textures,
			atlas->size * sizeof(texture), atlas->capacity * sizeof(texture));
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
		mlx_destroy_image(mlx_ptr, atlas->textures[i].img);
		++i;
	}
	free(atlas->textures);
}
