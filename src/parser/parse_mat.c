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
		.id = ' ', .tex_ids = {0, 0, 0, 0}, .orientation = 0, .type = MAT_OPEN,
	});
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){
		.id = '0', .tex_ids = {0, 0, 0, 0}, .orientation = 0, .type = MAT_FLOOR,
	});
	atlas_mat_add(&parser->s_data.mat_atlas, (t_material){.id = '1', .tex_ids
		= {texs[0], texs[1], texs[2], texs[3]}, .orientation = 0, .type
		= MAT_CUBE});
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
		|| !parse_mat_textures(parser, &line, tex_attrs, mat))
		return (-1);
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}

bool
	parser_mat(struct s_parser *parser)
{
	int	status;

	if (parser->s_data.mat_atlas.size == 0)
		init_atlas(parser);
	if (!*parser_trim_start(parser->line, " \t\n"))
		return (true);
	status = parse_mat_default(parser);
	if (status == -1)
		return (false);
	else if (status == 0)
		parser->state = PARSE_MAP; // TODO: PARSE_ENT
	return (true);
}
