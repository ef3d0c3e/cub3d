/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	app_setup(t_app *app)
{
	//if (!thread_pool_init(&app->pool, 16))
	//	return (false);
	if (!game_setup(app))
		return (false);
	app->z_buffer = xmalloc(sizeof(float) * (size_t)app->sizes.x);
	return (true);
}

void
	app_cleanup(t_app *app)
{
	//thread_pool_destroy(&app->pool);
	game_cleanup(app);
	free(app->z_buffer);
}
