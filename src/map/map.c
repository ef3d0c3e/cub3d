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
#include <cub3d.h>

void
	map_free(t_map *map)
{
	free(map->map);
}

t_material
	*map_get(t_app *app, int x, int y)
{
	t_atlas_id	id;

	if (x < 0 || y < 0
		|| x >= app->map.size_x || y >= app->map.size_y)
		return (NULL);
	id = app->map.map[x + y * app->map.size_x];
	if (id == 0 || id == (t_atlas_id)ATLAS_INVALID)
		return (NULL);
	return (&app->material_atlas.materials[id]);
}
