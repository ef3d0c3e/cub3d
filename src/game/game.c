/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

bool
	game_setup(t_app *app)
{
	if (!game_minimap_setup(app))
		return (false);
	player_setup(app);
	app->game.show_minimap = true;
	return (true);
}

void
	game_cleanup(t_app *app)
{
	(void)app;
}

void
	game_input(t_app *app)
{
	if (app->event.mouse_grab)
		player_input(app);
}

// TODO: Apply view bobbing
void
	draw_viewmodel(t_app *app)
{
	const t_weapon	*weapon = &app->assets.weapons[app->game.player.weapon_id];

	if (app->game.player.weapon_id == WEAPON_NONE)
		return ;
	weapon->draw(app, weapon,
		&app->game.player.weapons[app->game.player.weapon_id]);
}

/** @brief Draw stats hud */
static void
	draw_hud(t_app *app)
{
	const t_player	*player = &app->game.player;
	t_vec2			size;
	static char		bufs[2][64];

	ft_memcpy(bufs[0], "[ HP ", 5);
	itoa_buf(bufs[0] + 5, player->health);
	ft_memcpy(bufs[0] + ft_strlen(bufs[0]), " ]", 2);
	size = font_textsize(app, &pan_ctx(NULL)->font, bufs[0]);
	pan_cursor_set((t_vec2){0.f, .99f - size.y});
	pan_text(bufs[0]);
	if (player->weapon_id != WEAPON_NONE)
	{
		ft_memcpy(bufs[1], "[ AMMO ", 8);
		itoa_buf(bufs[1] + 7, player->weapons[player->weapon_id].ammo);
		ft_memcpy(bufs[1] + ft_strlen(bufs[1]), " ]", 3);
		size = font_textsize(app, &pan_ctx(NULL)->font, bufs[1]);
		pan_cursor_set((t_vec2){1.f - size.x, .99f - size.y});
		pan_text(bufs[1]);
	}
	pan_cursor_set((t_vec2){0, 0});
}

void
	game_ui(t_app *app)
{
	static char	fps[256] = "FPS ";

	map_state_update(app);
	render_frame(app);
	if (app->game.show_minimap)
		game_minimap_render(app);
	draw_viewmodel(app);
	draw_hud(app);
	pan_text("Cub3D ");
	pan_sameline();
	ftoa_buf(fps + 4, 1.f / app->frame_delta, 2);
	pan_text(fps);
	game_interact(app);
	game_debug(app);
	ent_update(app);
}
