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
	t_texture tex;

	tex.width = app->map.size_x;
	tex.height = app->map.size_y;
	tex.img = mlx_new_image(app->mlx_ptr, tex.width, tex.height);
	if (!tex.img)
		return (false);
	tex.path = NULL;
	app->game.minimap = (t_sprite){
		.texture = atlas_tex_get(&app->texture_atlas, atlas_tex_add(&app->texture_atlas, tex)),
		.background = 0x000000,
		.width = tex.width,
		.height = tex.height,
		.left = 0,
		.top = 0,
		.line_size = tex.width
	};
	for (int y = 0; y < tex.height; ++y)
	{
		for (int x = 0; x < tex.width; ++x)
		{
			t_color col = 0x0000FF;
			if (!map_get(app, x, y))
				col = 0xFFFFFF;
			else if (map_get(app, x, y)->type == MAT_CUBE)
				col = 0xFF0000;
			else if (map_get(app, x, y)->type == MAT_FLOOR)
				col = 0x00FF00;
			((t_color *)app->game.minimap.texture->img->data)[x + y * tex.width]
				= col;
		}

	}
	player_setup(app);
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
	
	const t_weapon	*weapon = &app->assets.weapons[app->game.player.weapon];
	float			f;
	float			y;
	int				anim;

	if (app->game.player.weapon == WEAPON_NONE)
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
	t_vec2		size;
	static char	bufs[3][64];

	ft_memcpy(bufs[0], "[ HP ", 5);
	itoa_buf(bufs[0] + 5, 97);
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
	itoa_buf(bufs[2] + 7, 12);
	ft_memcpy(bufs[2] + ft_strlen(bufs[2]), " ]", 2);
	size = font_textsize(app, &pan_ctx(NULL)->font, bufs[2]);
	pan_cursor_set((t_vec2){1.f - size.x, 1 - size.y});
	pan_text(bufs[2]);
	pan_cursor_set((t_vec2){0, 0});
}

void
	game_render(t_app *app)
{
	render_frame(app);
	// Draw the 5x5 sprite
	hud_draw(app, (t_draw_item){
		.type = DRAW_SPRITE,
		.draw.sprite = {
			.sprite = app->game.minimap,
			.color = 0xFFFFFF,
			.scale = (t_vec2){10.f, 10.f},
			.pos = {.5f, .5f},
		}
	});

	draw_viewmodel(app);
	draw_hud(app);
	
	pan_text("Cub3D");
	pan_push_columns("COL1", 3);
	if (pan_button("Test\001bb"))
	{
		printf("Clicked\n");
	}
	static int vali = 7;
	pan_slider_i("value", &vali, (const int [2]){-128, 128});
	static int vali2 = 7;
	pan_slider_i("yu", &vali2, (const int [2]){0, 10});
	static float valf = 0.5;
	pan_slider_f("fff", &valf, (const float [2]){-1, 5});
	pan_next_columns();
	if (pan_button("Hello"))
	{
		printf("Clicked Hello\n");
	}
	pan_button("Column layout");
	pan_button("After");
	pan_button("AAAAA");
	pan_next_columns();
	if (pan_button("Hello"))
	{
		printf("Clicked Hello\n");
	}
	pan_text("foobar");
	static bool val;
	if (pan_checkbox("Check", &val))
	{
		printf("Checkbox clicked\n");
	}
	pan_text("foobar");
	pan_pop_columns();
	pan_button("Column layout");
}
