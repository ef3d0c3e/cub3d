/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Parses the texture path string */
static bool
	parse_tex(
	struct s_parser *parser,
	const char *line,
	enum e_orientation orientation)
{
	size_t	start;
	size_t	len;

	start = 2;
	while (ft_strchr(" \t", line[start]))
		++start;
	line += start;
	len = ft_strlen(line);
	while (ft_strchr(" \t\n", line[len - 1]))
		--len;
	if (len == 0)
		return (parser_error_loc(parser, err(0, "Missing texture")), false);
	if (len < 4 || ft_strncmp(line + len - 4, ".xpm", 4))
		return (parser_error_loc(parser, err(0, "Invalid extension")), false);
	parser->s_data.textures[orientation] = xmalloc(len + 1);
	ft_memcpy(parser->s_data.textures[orientation], line, len);
	parser->s_data.textures[orientation][len] = 0;
	return (true);
}

int
	parse_hdr_texture(struct s_parser *parser, const char *line)
{
	enum e_orientation	i;
	const char			**field;

	i = ORI_NORTH;
	while (i++ <= ORI_WEST)
	{
		field = parser_hdr_fields((size_t)(i - 1), false);
		if (ft_strncmp(line, field[0], 2))
			continue ;
		if (parser->s_data.textures[i - 1])
			return (parser_error_loc(parser, err(err_style(err(0,
								"Duplicate texture '"), field[1], (t_text_style)
							{COL_YELLOW, 0, STYLE_BOLD}), "'")), -1);
		if (!parse_tex(parser, line, i - 1))
			return (-1);
		return (1);
	}
	return (0);
}
