/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>
#include <fcntl.h>

bool
	parse_line(struct s_parser *parser)
{
	parser->line = get_next_line(parser->fd);
	while (parser->line && parser->state != PARSE_ERROR)
	{
		++parser->line_num;
		if (parser->state == PARSE_HDR && !parser_parse_header(parser))
			parser->state = PARSE_ERROR;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	return (parser->state != PARSE_ERROR);
}

bool
	parse_map(const char *file)
{
	struct s_parser parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.file = file;
	parser.fd = -1;
	if (ft_strlen(file) < 4 || ft_strncmp(file + ft_strlen(file) - 4, ".cub",
		4))
		return (parser_error(err(err_style(err(0, "File '"),
		parser.file, (t_text_style){COL_CYAN, 0, 0}), "' has an incorrect "
		"extension.")), false);
	parser.fd = open(parser.file, O_RDONLY);
	if (parser.fd < 0)
		return (parser_error(err(err_style(err(0, "Failed to open "
		"file '"), parser.file, (t_text_style){COL_CYAN, 0, 0}), "'.")), false);
	parser.line = get_next_line(parser.fd);
	parser.line_num = 1;
	return (parser_error_loc(&parser, err_style(0, "Invalid token", (t_text_style){COL_GREEN, 0, STYLE_BOLD})), false);
	return (true);
}
