/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mat_attrs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

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
			if (!parser_expect_space(parser, line, oris[2 * i]))
				return (false);
			mat->orientation = i;
			return (true);
		}
		++i;
	}
	parser_error_loc(parser, err(0, "Expected material orientation after ID"));
	return (false);
}

/** @brief Check for duplicate and invalid material ID */
static bool
	validate_id(struct s_parser *parser, char id[2])
{
	static const char	*reserved = "NESW";
	const t_material	*mat = atlas_mat_get(&parser->s_data.mat_atlas, id[0]);

	if (mat)
		return (parser_error_loc(parser, err_style(err_style(err(0, "Duplicate "
							"material id: "), id, (t_text_style){COL_GREEN, 0,
						STYLE_BOLD}), "", (t_text_style){0, 0, 0})), false);
	if (ft_strchr(reserved, id[0]))
		return (parser_error_loc(parser, err_style(err_style(err(0, "Illegal "
							"material id: "), id, (t_text_style){COL_GREEN, 0,
						STYLE_BOLD}), "", (t_text_style){0, 0, 0})), false);
	return (true);
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
	if (!parser_expect_space(parser, &line, "MAT"))
		return (-1);
	if (ft_strncmp(line, ident, ft_strlen(ident)))
		return (0);
	if (!parser_expect_space(parser, &line, ident))
		return (-1);
	if (!ft_isprint(*line))
		return (parser_error_loc(parser, err(0, "Missing material ID")), -1);
	buf[0] = *line;
	buf[1] = 0;
	if (!parser_expect_space(parser, &line, buf) || !validate_id(parser, buf))
		return (-1);
	mat->id = buf[0];
	if (!parse_material_orientation(parser, &line, mat)
		|| !parse_mat_textures(parser, &line, tex_attrs, mat))
		return (-1);
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}
