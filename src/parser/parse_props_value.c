/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_props_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Parse the decimal part of a floating point value */
static bool
	parse_float_decimal_part(
	struct s_parser *parser,
	const char **line,
	const char *name,
	float *val)
{
	float	base;

	*line = *line + 1;
	base = .1f;
	if (!ft_isdigit(**line))
		return (parser_error_loc(parser, err_style(err_style(err(0, "Expected "
							"digits after '.' when parssing '"), name,
						(t_text_style){COL_CYAN, 0, STYLE_ITALIC}), "'",
				(t_text_style){0, 0, 0})), false);
	while (ft_isdigit(**line))
	{
		*val += (**line - '0') * base;
		base *= .1f;
		*line = *line + 1;
	}
	return (true);
}

/** @brief Parse a floating point value */
static bool
	parse_float(
	struct s_parser *parser,
	const char **line,
	const char *name,
	float *val)
{
	*val = 0;
	if (ft_isdigit(**line))
	{
		while (ft_isdigit(**line))
		{
			*val = *val * 10 + (**line - '0');
			*line = *line + 1;
		}
		if (**line == '.')
			return (parse_float_decimal_part(parser, line, name, val));
		return (true);
	}
	else if (**line == '.')
		return (parse_float_decimal_part(parser, line, name, val));
	parser_error_loc(parser, err_style(err_style(err(0, "Invalid floating point"
					" value when parsing '"), name, (t_text_style){COL_CYAN, 0,
				STYLE_ITALIC}), "'", (t_text_style){0, 0, 0}));
	return (false);
}

int
	parse_property_float(
	struct s_parser *parser,
	const char *name,
	float *value)
{
	const char	*line;

	line = parser_trim_start(parser->line, " \t");
	if (ft_strncmp(line, "PROP", 4))
		return (0);
	if (!parser_expect_space(parser, &line, "PROP"))
		return (-1);
	if (ft_strncmp(line, name, ft_strlen(name)))
		return (-2);
	if (!parser_expect_space(parser, &line, name))
		return (-1);
	if (!parse_float(parser, &line, name, value))
		return (-1);
	line = parser_trim_start(line, " \t");
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}

/** @brief Parse a material id value */
static bool
	parse_mat_id(
	struct s_parser *parser,
	const char **line,
	char *mat_id)
{
	const t_material	*mat;
	char				buf[2];

	*mat_id = 0;
	if (!ft_isprint(**line) || ft_strchr("NESW", **line))
		return (parser_error_loc(parser, err(0, "Invalid material id")), false);
	buf[0] = **line;
	buf[1] = 0;
	mat = atlas_mat_get(&parser->s_data.mat_atlas, **line);
	if (!mat)
		return (parser_error_loc(parser, err_style(err_style(err(0, "Invalid "
							"material id '"), buf, (t_text_style){COL_BLACK,
						COL_GREEN, STYLE_BOLD}), "': Unknown material",
				(t_text_style){0, 0, 0})), false);
	if (mat->type != MAT_FLOOR)
		return (parser_error_loc(parser, err_style(err_style(err(0, "Invalid "
							"material id '"), buf, (t_text_style){COL_BLACK,
						COL_GREEN, STYLE_BOLD}), "': Material is not a FLOOR",
				(t_text_style){0, 0, 0})), false);
	*line = *line + 1;
	return (true);
}

int
	parse_property_mat(
	struct s_parser *parser,
	const char *name,
	char *mat_id)
{
	const char	*line;

	line = parser_trim_start(parser->line, " \t");
	if (ft_strncmp(line, "PROP", 4))
		return (0);
	if (!parser_expect_space(parser, &line, "PROP"))
		return (-1);
	if (ft_strncmp(line, name, ft_strlen(name)))
		return (-2);
	if (!parser_expect_space(parser, &line, name))
		return (-1);
	if (!parse_mat_id(parser, &line, mat_id))
		return (-1);
	line = parser_trim_start(line, " \t");
	if (*line && *line != '\n')
		return (parser_error_loc(parser, err(0, "Unexpected token")), -1);
	return (1);
}
