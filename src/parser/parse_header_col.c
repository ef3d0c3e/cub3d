/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_col.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Parse a single integer for colors */
static int
	parse_int(struct s_parser *parser, const char **line, const char *field)
{
	size_t	pos;
	int		val;

	*line = parser_trim_start(*line, " \t\n");
	if (!ft_isdigit(**line) || !**line)
		return (parser_error_loc(parser, err(err(err(0, "Invalid color "
							"value for "), field), ". Expected a value in "
					"the range [0, 255]")), -1);
	pos = 0;
	val = -1;
	while (ft_isdigit((*line)[pos]))
	{
		val = val * 10 + (*line)[pos++] - '0';
		if (val > 255)
			return (parser_error_loc(parser, err(err(err(0, "Invalid color "
								"value for "), field), ". Expected a value in "
						"the range [0, 255]")), -1);
	}
	*line = parser_trim_start(*line + pos, " \t\n");
	return (val);
}

/** @brief Parse a complete color value (comma separated ingegers) */
static bool
	parse_color_value(
	struct s_parser *parser,
	const char **line,
	t_color *color)
{
	static const char	*fields[3] = {"Red", "Green", "Blue"};
	int					vals[3];
	size_t				i;

	i = 0;
	while (i < 3)
	{
		vals[i] = parse_int(parser, line, fields[i]);
		if (vals[i] == -1)
			return (false);
		if ((i != 2 && (*line)[0] != ','))
			return (parser_error_loc(parser, err(0, "Expected a triplet for "
						"color")), false);
		if (i != 2)
			*line = ++*line;
		++i;
	}
	if (**line)
		return (parser_error_loc(parser, err(0, "Leftover content after color")
			), false);
	*color = (t_color)(vals[0] | (vals[1] << 8) | (vals[2] << 16));
	return (true);
}

int
	parse_hdr_color(struct s_parser *parser, const char *line)
{
	enum e_orientation	i;
	const char			**field;

	i = 0;
	while (i++ < 2)
	{
		field = parser_hdr_fields(i - 1, true);
		if (ft_strncmp(line, field[0], 1))
			continue ;
		if (parser->s_data.colors[i - 1] != (t_color)COLOR_UNINIT)
			return (parser_error_loc(parser, err(err_style(err(0,
								"Duplicate color for '"), field[1],
							(t_text_style){COL_YELLOW, 0, STYLE_BOLD}),
					"'")), -1);
		++line;
		if (!parse_color_value(parser, &line, &parser->s_data.colors[i - 1]))
			return (-1);
		return (1);
	}
	return (0);
}
