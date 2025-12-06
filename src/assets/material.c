/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <assets/assets.h>

t_atlas_id
	atlas_mat_add(t_material_atlas *atlas, t_material material)
{
	if (atlas->size == atlas->capacity)
	{
		atlas->capacity = atlas->capacity * 2 + !atlas->capacity * 16;
		atlas->materials = xrealloc(atlas->materials,
				atlas->size * sizeof(material),
				atlas->capacity * sizeof(material));
	}
	atlas->materials[atlas->size++] = material;
	return ((t_atlas_id)(atlas->size - 1));
}

void
	atlas_mat_free(t_material_atlas *atlas)
{
	free(atlas->materials);
}

const t_material
	*atlas_mat_get(const t_material_atlas *atlas, char ch)
{
	size_t	i;

	if (ft_strchr("NESW", ch))
		return (atlas_mat_get(atlas, '0'));
	i = 0;
	while (i < atlas->size)
	{
		if (atlas->materials[i].id == ch)
			return (&atlas->materials[i]);
		++i;
	}
	return (NULL);
}
