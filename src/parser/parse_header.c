/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Gets the identifier and display name of a header field */
static const char
	**fields(size_t id, bool color)
{
	static const char	*colors[] = {"F", "Floor Color", "C", "Ceiling Color"};
	static const char	*textures[] = {"NO", "North", "WE", "West",
	"SO", "South", "EA", "East"};

	if (color)
		return (&colors[id * 2]);
	return (&textures[id * 2]);
}

/** @brief Attempt to parse a basic texture with orientation */
static int
	parse_texture(struct s_parser *parser, const char *line)
{
	size_t		i;
	const char	**field;

	i = 0;
	while (i++ < 4)
	{
		field = fields(i - 1, false);
		if (ft_strncmp(line, field[0], 2))
			continue ;
		if (parser->s_data.textures[i - 1])
			return (parser_error_loc(parser, err(err_style(err(0,
				"Duplicate texture '"), field[1], (t_text_style){COL_YELLOW, 0,
				STYLE_BOLD}), "'")), -1);
		
		return (1);
	}
	return (0);
}

bool
	parser_parse_header(struct s_parser *parser)
{
	const char	*line = parser_trim_start(parser->line, " \t");

	if (!line[0])
		return (false);
}
