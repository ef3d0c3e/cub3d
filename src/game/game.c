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
	player_input(app);
}

// TODO: Apply view bobbing
void
	draw_viewmodel(t_app *app)
{
	
	const t_weapon	*weapon = &app->assets.weapons[app->game.player.weapon_id];
	float			f;
	float			y;
	int				anim;

	if (app->game.player.weapon_id == WEAPON_NONE)
		return ;
	anim = 0;
	if (app->game.player.weapon_anim != 0)
		anim = 1 + (int)((float)(sprite_sheet_anim_count(&weapon->view_model)
					- 2) *(weapon->anim_shoot_time
					- app->game.player.weapon_anim) / weapon->anim_shoot_time);
	f = .65f * (float)app->sizes.x / (float)weapon->view_model.width;
	y = 1.1f - (float)weapon->view_model.height * f * .5f / (float)app->sizes.y;
	hud_draw(app, (t_draw_item){
		.type = DRAW_SPRITE,
		.draw.sprite = {
			.sprite = sprite_sheet_get(&weapon->view_model, 0, anim),
			.color = 0xFFFFFF,
			.scale = (t_vec2){f, f},
			.pos = {.37f, y},
		}
	});
}

/** @brief Draw stats hud */
static void
	draw_hud(t_app *app)
{
	const t_player	*player = &app->game.player;
	t_vec2			size;
	static char		bufs[3][64];

	ft_memcpy(bufs[0], "[ HP ", 5);
	itoa_buf(bufs[0] + 5, player->health);
	ft_memcpy(bufs[0] + ft_strlen(bufs[0]), " ]", 2);
	size = font_textsize(app, &pan_ctx(NULL)->font, bufs[0]);
	pan_cursor_set((t_vec2){0.f, 1 - size.y});
	pan_text(bufs[0]);
	ft_memcpy(bufs[1], "[ SCORE ", 8);
	itoa_buf(bufs[1] + 8, 123456);
	ft_memcpy(bufs[1] + ft_strlen(bufs[1]), " ]", 2);
	size = font_textsize(app, &pan_ctx(NULL)->font, bufs[1]);
	pan_cursor_set((t_vec2){.5f - .5f * size.x, 1 - size.y});
	pan_text(bufs[1]);
	ft_memcpy(bufs[2], "[ AMMO ", 7);
	itoa_buf(bufs[2] + 7, player->weapons[player->weapon_id].ammo);
	ft_memcpy(bufs[2] + ft_strlen(bufs[2]), " ]", 2);
	size = font_textsize(app, &pan_ctx(NULL)->font, bufs[2]);
	pan_cursor_set((t_vec2){1.f - size.x, 1 - size.y});
	pan_text(bufs[2]);
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
