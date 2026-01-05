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

/** @brief Measure frame time and sleeps using spinlock to attempt to limit the
 * framerate */
static void
	frame_time(t_app *app, bool is_start)
{
	static struct timeval	t[2];
	time_t					sec;
	long					usec;
	float					rem;

	if (is_start && (gettimeofday(&t[0], NULL), 1))
		return ;
	gettimeofday(&t[1], NULL);
	sec = t[1].tv_sec - t[0].tv_sec;
	usec = t[1].tv_usec - t[0].tv_usec;
	usec += 1000000L * (usec < 0) + (0 * --sec);
	if (usec < 0 && (--sec, 1))
		usec += 1000000L;
	app->frame_delta = (float)sec + 1e-6f * (float)usec;
	rem = app->map.props.frame_time - app->frame_delta;
	while (rem > 0.f)
	{
		gettimeofday(&t[1], NULL);
		sec = t[1].tv_sec - t[0].tv_sec;
		usec = t[1].tv_usec - t[0].tv_usec;
		if (usec < 0 && (--sec, 1))
			usec += 1000000L;
		rem -= (float)sec + 1e-6f * (float)usec;
		app->frame_delta = app->map.props.frame_time;
	}
}

/** @brief Render and update cursor */
static void
	ui_cursor(t_app *app)
{
	const t_font	font = font_new(&app->hud.font, 0xFFFFFF, 0.7f);
	static char		glyph[2];
	t_vec2			pos;

	glyph[0] = "\003\004"[!app->event.mouse_grab];
	pos = (t_vec2){.5f, .5f};
	if (app->event.mouse_grab)
		mlx_mouse_move(app->mlx_ptr, app->mlx_window,
			app->sizes.x / 2, app->sizes.y / 2);
	else
	{
		pos.x = ((float)app->event.mouse_pos.x + .5f * (float)font.base_size.x * font.scale.x) / (float)app->sizes.x;
		pos.y = ((float)app->event.mouse_pos.y + .5f * (float)font.base_size.y * font.scale.y) / (float)app->sizes.y;
	}
	hud_draw(app, (t_draw_item){
		.type = DRAW_TEXT,
		.draw.text = {
		.text = glyph,
		.font = font,
		.pos = pos,
	}});

}

/** @brief Frame draw function */
static int
	ui_update(t_app *app)
{
	if (app->frame_delta == 0)
		app->frame_delta = 1.f;
	++app->frame;
	app->event.mouse_grab = true;
	frame_time(app, true);
	ft_memset(app->framebuffer->data, 0,
		(size_t)app->sizes.x * (size_t)app->sizes.y * sizeof(t_color));
	game_input(app);
	game_render(app);
	ui_cursor(app);
	hud_render(app);
	mlx_put_image_to_window(app->mlx_ptr, app->mlx_window,
		app->framebuffer, 0, 0);
	pan_context_reset(app);
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
	hud_init(app);
	mlx_mouse_hide(app->mlx_ptr, app->mlx_window);
	return (true);
}

void
	ui_cleanup(t_app *app)
{
	hud_free(app);
	event_cleanup(app);
	mlx_destroy_image(app->mlx_ptr, app->framebuffer);
}
