/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

static bool
	set_spawn(struct s_parser *parser, int line_pos)
{
	static const enum e_orientation	map[] = {
	['N'] = ORI_NORTH,
	['E'] = ORI_WEST,
	['S'] = ORI_SOUTH,
	['W'] = ORI_WEST,
	};
	const char						dir = parser->line[line_pos];

	if (parser->s_data.player_orientation != ORI_NONE)
		return (parser_error_loc(parser, err(0, "Duplicate spawn")), false);
	parser->s_data.player_orientation = map[(size_t)dir];
	parser->s_data.player_spawn.x = line_pos;
	parser->s_data.player_spawn.y = (int)parser->s_data.lines_size;
	return (true);
}

static int
	validate_line(struct s_parser *parser)
{
	char	buf[2];
	int		i;

	i = 0;
	buf[1] = 0;
	while (parser->line[i] && parser->line[i] != '\n')
	{
		buf[0] = parser->line[i];
		if (ft_strchr("NESW", parser->line[i]))
		{
			if (!set_spawn(parser, i))
				return (-1);
		}
		else if (!atlas_mat_get(&parser->s_data.mat_atlas, parser->line[i]))
			return (parser_error_loc(parser, err_style(err_style(err(0, "Invali"
								"d material in map '"), buf, (t_text_style){
							COL_BLACK, COL_GREEN, STYLE_BOLD}), "'",
					(t_text_style){0, 0, 0})), -1);
		++i;
	}
	return (i);
}

bool
	parser_map(struct s_parser *parser)
{
	int	len;

	if (parser->s_data.lines_size == parser->s_data.lines_capacity)
	{
		parser->s_data.lines_capacity = parser->s_data.lines_capacity * 2ULL
			+ !parser->s_data.lines_size * 16ULL;
		parser->s_data.lines = xrealloc(parser->s_data.lines,
				parser->s_data.lines_size * sizeof(char *),
				parser->s_data.lines_capacity * sizeof(char *));
	}
	len = validate_line(parser);
	if (len == -1)
		return (false);
	parser->s_data.lines[parser->s_data.lines_size] = xmalloc((size_t)len + 1);
	ft_memcpy(parser->s_data.lines[parser->s_data.lines_size], parser->line,
		(size_t)len);
	parser->s_data.lines[parser->s_data.lines_size++][len] = 0;
	++parser->s_data.map_height;
	if (len > parser->s_data.map_width)
		parser->s_data.map_width = len;
	return (true);
}
