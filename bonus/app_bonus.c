/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d_bonus.h>

/** @brief Initialize the default floor material */
static bool
	init_default_floor(t_app *app)
{
	const t_atlas_id	id = atlas_mat_get_id(&app->material_atlas, '0');
	t_img				*img;

	img = mlx_new_image(app->mlx_ptr, 1, 1);
	if (!img)
		return (false);
	((t_color *)img->data)[0] = app->map.colors[1];
	app->material_atlas.materials[id].tex_ids[0]
		= atlas_tex_add(&app->texture_atlas, (t_texture){1, 1, NULL, img});
	img = mlx_new_image(app->mlx_ptr, 1, 1);
	if (!img)
		return (false);
	((t_color *)img->data)[0] = app->map.colors[0];
	app->material_atlas.materials[id].tex_ids[1]
		= atlas_tex_add(&app->texture_atlas, (t_texture){1, 1, NULL, img});
	return (true);
}

bool
	app_setup(t_app *app)
{
	if (!init_default_floor(app))
		return (false);
	if (!thread_pool_init(&app->pool, 8))
		return (false);
	if (!game_setup(app))
		return (false);
	app->z_buffer = xmalloc(sizeof(float) * (size_t)app->sizes.x);
	return (true);
}

void
	app_cleanup(t_app *app)
{
	thread_pool_destroy(&app->pool);
	game_cleanup(app);
	free(app->z_buffer);
}
