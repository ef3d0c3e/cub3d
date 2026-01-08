/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>
#include <parser/parser.h>

/** @brief Fill the map using the parsed map content */
static void
	fill_map(const struct s_parser *parser, t_app *app)
{
	t_pos	pos;
	size_t	len;
	char	id;

	pos = (t_pos){0, 0};
	while ((size_t)pos.y < parser->s_data.lines_size)
	{
		len = ft_strlen(parser->s_data.lines[pos.y]);
		while ((size_t)pos.x < len)
		{
			id = parser->s_data.lines[pos.y][pos.x];
			if (ft_strchr("NESW", id))
				id = app->map.props.player_spawn;
			app->map.map[pos.x + app->map.size_x * pos.y]
				= atlas_mat_get_id(&app->material_atlas, id);
			if (atlas_mat_get(&app->material_atlas, id)->type == MAT_DOOR)
				map_data_set(app, pos.x, pos.y, map_data_door());
			++pos.x;
		}
		++pos.y;
		pos.x = 0;
	}
}

/** @brief Setup entities */
static void
	map_setup_ent(struct s_parser *parser, t_app *app)
{
	size_t				i;
	struct s_parser_ent	*ent;

	ent_setup(app);
	i = 0;
	while (i < parser->s_data.ents_size)
	{
		ent = &parser->s_data.ents[i];
		ent_spawn(app, ent->id, (t_entity_data){
			.acceleration = (t_vec2){0, 0},
			.velocity = (t_vec2){0, 0},
			.position = ent->pos,
			.angles = ent->angles,
			.anim_state = (t_pos){0, 0},
			.flip = false,
		});
		++i;
	}
}

void
	parser_make_map(struct s_parser *parser, t_app *app)
{
	app->map.props = parser->s_data.properties;
	app->map.player_spawn = parser->s_data.player_spawn;
	app->map.player_orientation = parser->s_data.player_orientation;
	app->map.colors[0] = parser->s_data.colors[0];
	app->map.colors[1] = parser->s_data.colors[1];
	app->material_atlas = parser->s_data.mat_atlas;
	app->texture_atlas = parser->s_data.tex_atlas;
	parser->s_data.mat_atlas.materials = NULL;
	parser->s_data.mat_atlas.size = 0;
	parser->s_data.tex_atlas.textures = NULL;
	parser->s_data.tex_atlas.size = 0;
	app->map.size_x = parser->s_data.map_width;
	app->map.size_y = parser->s_data.map_height;
	app->map.map = xmalloc(sizeof(t_atlas_id)
			* (size_t)app->map.size_x * (size_t)app->map.size_y);
	ft_memset(app->map.map, 0, sizeof(t_atlas_id)
		* (size_t)app->map.size_x * (size_t)app->map.size_y);
	parser->s_data.lines[app->map.player_spawn.y][app->map.player_spawn.x]
		= app->map.props.player_spawn;
	app->map.map_data = rb_new(map_data_cmp, NULL, free);
	fill_map(parser, app);
	map_setup_ent(parser, app);
}
