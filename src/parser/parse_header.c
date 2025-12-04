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

const char
	**parser_hdr_fields(size_t id, bool is_color)
{
	static const char	*colors[] = {"F", "Floor", "C", "Ceiling"};
	static const char	*textures[] = {"NO", "North", "EA", "East",
		"SO", "South", "WE", "West"};

	if (is_color)
		return (&colors[id * 2]);
	return (&textures[id * 2]);
}

/** @brief Check for missing fields in the header */
static bool
	hdr_check_missing(struct s_parser *parser)
{
	size_t		i;
	bool		status;

	status = true;
	i = 0;
	while (i++ < 4)
	{
		if (parser->s_data.textures[i - 1])
			continue ;
		parser_error_file(parser, err_style(err_style(err(0, "Missing texture "
						"for '"), parser_hdr_fields(i - 1, false)[1],
					(t_text_style){COL_YELLOW, 0, STYLE_BOLD}), "'",
				(t_text_style){0, 0, 0}));
		status = false;
	}
	while (i++ < 7)
	{
		if (parser->s_data.colors[i - 6] != (t_color)COLOR_UNINIT)
			continue ;
		parser_error_file(parser, err_style(err_style(err(0, "Missing color for"
						" '"), parser_hdr_fields(i - 6, true)[1], (t_text_style)
				{COL_YELLOW, 0, STYLE_BOLD}), "'", (t_text_style){0, 0, 0}));
		status = false;
	}
	return (status);
}

bool
	parser_hdr(struct s_parser *parser)
{
	const char	*line = parser_trim_start(parser->line, " \t\n");
	int			status;

	if (!line[0])
		return (true);
	status = parse_hdr_texture(parser, line);
	if (status == 0)
		status = parse_hdr_color(parser, line);
	if (status == -1)
		return (false);
	if (status == 0)
	{
		if (!hdr_check_missing(parser))
			return (false);
		parser->state = PARSE_MAT;
	}
	return (true);
}
