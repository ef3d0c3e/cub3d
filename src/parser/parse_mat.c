/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Initialize the atlases with the header's textures and default
 * materials */
static void
	init_atlas(struct s_parser *parser)
{
	t_atlas_id	texs[4];
	t_texture	tex;

	ft_memset(&tex, 0, sizeof(tex));
	tex.path = parser->s_data.textures[0];
	texs[0] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[0] = NULL;
	tex.path = parser->s_data.textures[1];
	texs[1] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[1] = NULL;
	tex.path = parser->s_data.textures[2];
	texs[2] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[2] = NULL;
	tex.path = parser->s_data.textures[3];
	texs[3] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	parser->s_data.textures[3] = NULL;
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){
		.id = '0', .tex_ids = {0, 0, 0, 0}, .orientation = 0, .type = MAT_FLOOR,
	});
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){
		.id = '1',
		.tex_ids = {texs[0], texs[1], texs[2], texs[3]},
		.orientation = 0,
		.type = MAT_CUBE,
	});
}

bool
	expect_space(struct s_parser *parser, const char **line, const char *after)
{
	const size_t	after_len = ft_strlen(after);
	const char		*advanced = parser_trim_start(*line + after_len, " \t");

	if (advanced != *line + after_len)
	{
		*line = advanced;
		return (true);
	}
	parser_error_loc(parser, err_style(err_style(err(0, "Expected a space after"
					" '"), after, (t_text_style){COL_YELLOW, 0, STYLE_BOLD}),
			"'", (t_text_style){0, 0, 0}));
	return (false);
}

/**
 * @brief Parse the material's orientation
 *
 * @param parser The parser
 * @param line The material definition line
 * @param mat The material
 * @return `true` on success, `false` on errors
 */
static bool
	parse_material_orientation(
	struct s_parser *parser,
	const char **line,
	t_material *mat)
{
	static const char	*oris[] = {"N", "North", "E", "East", "S", "South",
		"W", "West"};
	enum e_orientation	i;

	if (mat->orientation == ORI_NONE)
		return (true);
	i = ORI_NORTH;
	while (i <= ORI_WEST)
	{
		if (**line == oris[2 * i][0])
		{
			if (!expect_space(parser, line, oris[2 * i]))
				return (false);
			mat->orientation = i;
			return (true);
		}
		++i;
	}
	parser_error_loc(parser, err(0, "Expected material orientation after ID"));
	return (false);
}

/**
 * @brief Parse a single texture attribute
 */
static int
	parse_tex_prop(
	struct s_parser *parser,
	const char **line,
	const char **tex,
	const char **out)
{
	size_t	i;

	if (out[1])
		return (parser_error_loc(parser, err_style(err_style(err(0, "Duplicate "
							"texture '"), tex[1], (t_text_style){COL_YELLOW, 0,
						STYLE_BOLD}), "'", (t_text_style){0, 0, 0})), -1);
	if (ft_strncmp(*line, tex[0], ft_strlen(tex[0])))
		return (0);
	*line += ft_strlen(tex[0]);
	if (**line != '=')
		return (parser_error_loc(parser, err_style(err_style(err(0, "Expected '"
							"=' after '"), tex[0], (t_text_style){COL_YELLOW, 0,
						STYLE_BOLD}), "'", (t_text_style){0, 0, 0})), -1);
	++*line;
	out[0] = *line;
	i = 0;
	while (!ft_strchr(" \t\n", (*line)[i]))
		++i;
	if (!i)
		return (parser_error_loc(parser, err_style(err_style(err(0, "Empty '"),
						tex[1], (t_text_style){COL_YELLOW, 0, STYLE_BOLD}),
				"' texture", (t_text_style){0, 0, 0})), -1);
	*line += i;
	out[1] = *line;
	return (1);
}

static bool
	validate_textures(
	struct s_parser *parser,
	const char ***attrs_parsed,
	const size_t *counts,
	t_material *mat)
{
	t_err_str	msg;
	t_texture	tex;
	size_t		i;

	i = 0;
	ft_memset(&tex, 0, sizeof(tex));
	if (counts[0] != counts[1])
	{
		msg = err(0, "Missing textures");
		while (i++ < counts[1])
		{
			if (!attrs_parsed[1][2 * i - 1])
				msg = err_style(err_style(msg, " ", (t_text_style){0, 0, 0}),
						attrs_parsed[0][2 * i - 1], (t_text_style){COL_YELLOW,
						0, STYLE_BOLD});
		}
		return (parser_error_loc(parser, msg), false);
	}
	while (i < counts[0])
	{
		tex.path = ft_strndup(attrs_parsed[1][2 * i], (size_t)(attrs_parsed[1]
				[2 * i] - attrs_parsed[1][2 * i + 1]));
		mat->tex_ids[i++] = atlas_tex_add(&parser->s_data.tex_atlas, tex);
	}
	return (true);
}

static bool
	parse_material_textures(
	struct s_parser *parser,
	const char **line,
	const char **tex_attrs,
	t_material *mat)
{
	const char		*texs[8];
	size_t			i;
	int				s;
	size_t			counts[2];

	ft_memset(texs, 0, sizeof(texs));
	ft_memset(counts, 0, sizeof(counts));
	while (tex_attrs[2 * counts[1]])
		++counts[1];
	while (**line && **line != '\n')
	{
		i = 0;
		while (tex_attrs[i * 2])
		{
			printf("status=%d/%s\n", 0, *line);
			s = parse_tex_prop(parser, line, &tex_attrs[2 * i], &texs[2 * i]);
			++i;
			if (s == 0)
				continue ;
			if (s == -1)
				return (false);
			++counts[0];
			*line = parser_trim_start(*line, " \t");
		}
	}
	return (validate_textures(parser, (const char **[2]){tex_attrs, texs},
		counts, mat));
}

int
	parse_material(
	struct s_parser *parser,
	const char *ident,
	const char **tex_attrs,
	t_material *mat)
{
	const char	*line;
	char		buf[2];

	line = parser_trim_start(parser->line, " \t");
	if (ft_strncmp(line, "MAT", 3))
		return (0);
	if (!expect_space(parser, &line, "MAT"))
		return (-1);
	if (ft_strncmp(line, ident, ft_strlen(ident)))
		return (0);
	if (!expect_space(parser, &line, ident))
		return (-1);
	if (!ft_isprint(*line))
		return (parser_error_loc(parser, err(0, "Missing material ID")), -1);
	buf[0] = *line;
	buf[1] = 0;
	if (!expect_space(parser, &line, buf))
		return (-1);
	mat->id = buf[0];
	if (!parse_material_orientation(parser, &line, mat)
		|| !parse_material_textures(parser, &line, tex_attrs, mat))
		return (-1);
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}

bool
	parser_mat(struct s_parser *parser)
{
	if (parser->s_data.mat_atlas.size == 0)
		init_atlas(parser);
	if (!*parser_trim_start(parser->line, " \t\n"))
		return (true);
	t_material cube;
	cube.orientation = ORI_NONE;
	cube.id = 0;
	cube.type = MAT_CUBE;
	const char *texs[] = {
		"NO", "North",
		"EA", "East",
		"SO", "South",
		"WE", "West",
		NULL
	};
	parse_material(parser, "CUBE", texs, &cube);
	return (true);
}
