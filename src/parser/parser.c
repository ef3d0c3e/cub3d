/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>

#include <cub3d.h>
#include <parser/parser.h>

/** @brief Parses the input file, line-by-line */
static bool
	parse_line(struct s_parser *parser)
{
	parser->line = get_next_line(parser->fd);
	while (parser->line)
	{
		++parser->line_num;
		if (parser->state == PARSE_HDR && !parser_hdr(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_MAT && !parser_mat(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_PROPS && !parser_props(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_ENT && !parser_entities(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_MAP && !parser_map(parser))
			parser->state = PARSE_ERROR;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	if (parser->state != PARSE_MAP)
		return (parser_error_file(parser, err(0, "Unexpected end of file")), 0);
	return (parser->state != PARSE_ERROR && parser_validate(parser));
}

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
			++pos.x;
		}
		++pos.y;
		pos.x = 0;
	}
}

/** @brief Make a map from the parsed data */
static void
	make_map(struct s_parser *parser, t_app *app)
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
	fill_map(parser, app);
}

bool
	parse_map(const char *file, t_app *app)
{
	struct s_parser	parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.file = file;
	parser.fd = -1;
	parser.s_data.player_orientation = ORI_NONE;
	parser.s_data.colors[0] = (t_color)COLOR_UNINIT;
	parser.s_data.colors[1] = (t_color)COLOR_UNINIT;
	if (ft_strlen(file) < 4 || ft_strncmp(file + ft_strlen(file) - 4, ".cub",
			4))
		return (parser_error(err_style(err_style(err(0, "File '"),
						parser.file, (t_text_style){COL_CYAN, 0, 0}), "' has an"
				" incorrect extension.", (t_text_style){0, 0, 0})),
				parser_free(&parser), false);
	parser.fd = open(parser.file, O_RDONLY);
	if (parser.fd < 0)
		return (parser_error(err(err_style(err(0, "Failed to open file '"),
						parser.file, (t_text_style){COL_CYAN, 0, 0}), "'.")),
		parser_free(&parser), false);
	if (!parse_line(&parser))
		return (parser_free(&parser), false);
	make_map(&parser, app);
	parser_free(&parser);
	return (true);
}

void
	parser_free(struct s_parser *parser)
{
	size_t	i;

	free(parser->s_data.textures[0]);
	free(parser->s_data.textures[1]);
	free(parser->s_data.textures[2]);
	free(parser->s_data.textures[3]);
	atlas_mat_free(&parser->s_data.mat_atlas);
	atlas_tex_free(NULL, &parser->s_data.tex_atlas);
	i = 0;
	while (i < parser->s_data.lines_size)
		free(parser->s_data.lines[i++]);
	free(parser->s_data.lines);
	free(parser->line);
	if (parser->fd != -1)
		close(parser->fd);
}
