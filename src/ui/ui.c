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
#include <sys/time.h>

static void
	frame_time(t_app *app, bool is_start)
{
	static struct timeval	start;
	static struct timeval	end;
	time_t					sec;
	long					usec;
	float					rem;

	if (is_start && gettimeofday(&start, NULL))
		return ;
	gettimeofday(&end, NULL);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	if (usec < 0 && (--sec, 1))
		usec += 1000000L;
	app->frame_delta = (float)sec + 1e-6f * (float)usec;
	rem = app->map.props.frame_time - app->frame_delta;
	if (rem <= 0.0)
		return ;
	while (rem < app->map.props.frame_time)
	{
		gettimeofday(&end, NULL);
		sec = end.tv_sec - start.tv_sec;
		usec = end.tv_usec - start.tv_usec;
		if (usec < 0 && (--sec, 1))
			usec += 1000000L;
		rem = (float)sec + 1e-6f * (float)usec;
	}
	app->frame_delta = app->map.props.frame_time;
}

/** @brief Frame draw function */
static int
	ui_update(t_app *app)
{
	char buf[128];


	ft_memset(app->framebuffer->data, 0, app->sizes.x * app->sizes.y * 4);
	if (app->frame_delta == 0)
		app->frame_delta = 1.f;
	frame_time(app, true);
	sprintf(buf, "FPS = %d", (int)(1.f / app->frame_delta));
	hud_text(app, (t_pos){64, 65}, buf);
	mlx_put_image_to_window(app->mlx_ptr, app->mlx_window,
		app->framebuffer, 0, 0);
	event_update(app);
	frame_time(app, false);
	
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
