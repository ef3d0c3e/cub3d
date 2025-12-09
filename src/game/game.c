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
}

void
	game_input(t_app *app)
{
	player_input(app);
}

void
	game_render(t_app *app)
{
	// Draw the 5x5 sprite
	hud_draw(app, (t_draw_item){
		.type = DRAW_SPRITE,
		.draw.sprite = {
			.sprite = app->game.minimap,
			.color = 0xFFFFFF,
			.scale = (t_vec2){10.f, 10.f},
			.pos = {.5f, .1f},
		}
	});

	const char **items[] = {
		(const char *[]){"Foo", "bar", "quz", NULL},
		(const char *[]){"test", "lorem", "ipsum", NULL},
		(const char *[]){"dolor", "sit", NULL},
		NULL
	};
	static t_pos pos;
	t_pos move = (t_pos){1, 0};
	move.y = ui_key_pressed(app, KEY_ARROW_RIGHT) - ui_key_pressed(app, KEY_ARROW_LEFT);
	move.x = ui_key_pressed(app, KEY_ARROW_DOWN) - ui_key_pressed(app, KEY_ARROW_UP);
	hud_menu_move(items, &pos, move);
	hud_menu(app, items, pos);

	hud_button("Click me");
}

	/*
	const char **items[] = {
		(const char *[]){"Foo", "bar", "quz", NULL},
		(const char *[]){"test", "lorem", "ipsum", NULL},
		(const char *[]){"dolor", "sit", NULL},
		NULL
	};
	static t_pos pos;
	t_pos move = (t_pos){1, 0};
	move.y = ui_key_pressed(app, KEY_ARROW_RIGHT) - ui_key_pressed(app, KEY_ARROW_LEFT);
	move.x = ui_key_pressed(app, KEY_ARROW_DOWN) - ui_key_pressed(app, KEY_ARROW_UP);
	hud_menu_move(items, &pos, move);
	hud_menu(app, items, pos);
	*/
	/*
	hud_draw(app, (t_draw_item){
		.type = DRAW_TEXT_SHADOW,
		.draw.text_shadow = {
			.text = "Hello",
			.scale = 2,
			.color = 0xFF0000,
			.pos = {.5, .5},
			.color_shadow = 0x00FF00,
		}
	});
	*/
