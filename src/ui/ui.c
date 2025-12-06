/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

static int
	ui_update(t_app *app)
{
	const float	dt = app->map.props.frame_time;

	mlx_put_image_to_window(app->mlx_ptr, app->mlx_window,
		app->framebuffer, 0, 0);
	event_update(app);
	return (0);
}

bool
	ui_setup(t_app *app)
{
	app->framebuffer = mlx_new_image(app->mlx_ptr, app->sizes.x, app->sizes.y);
	event_setup(app);
	mlx_loop_hook(app->mlx_ptr, ui_update, app);
	return (true);
}

void
	ui_cleanup(t_app *app)
{
	event_cleanup(app);
	mlx_destroy_image(app->mlx_ptr, app->framebuffer);
}
