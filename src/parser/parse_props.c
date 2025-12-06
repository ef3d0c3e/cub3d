/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_props.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Setup default property values */
static void
	init_properties(struct s_parser *parser)
{
	parser->s_data.parsing_properties = true;
	parser->s_data.properties.accelerate = 1.f;
	parser->s_data.properties.friction = 0.95f;
	parser->s_data.properties.frame_time = 1.f / 60.f;
}

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

/** @brief Parse a single property */
static int
	parse_property(
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

bool
	parser_props(struct s_parser *parser)
{
	int	status;

	if (!parser->s_data.parsing_properties)
		init_properties(parser);
	if (!*parser_trim_start(parser->line, " \t\n"))
		return (true);
	status = parse_property(parser, "accelerate",
			&parser->s_data.properties.accelerate);
	if (status == 0 || status == -2)
		status = parse_property(parser, "friction",
				&parser->s_data.properties.friction);
	if (status == 0 || status == -2)
		status = parse_property(parser, "frame_time",
				&parser->s_data.properties.frame_time);
	if (status == -2)
		return (parser_error_loc(parser, err(0, "Unknown property name")),
			false);
	if (status == -1)
		return (false);
	else if (status == 0)
		parser->state = PARSE_MAP; // TODO: PARSE_ENT
	return (true);
}
