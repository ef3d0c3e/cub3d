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

/** @brief Parses the input file, line-by-line */
static bool
	parse_line(struct s_parser *parser)
{
	parser->line = get_next_line(parser->fd);
	while (parser->line)
	{
		++parser->line_num;
		if (parser->state == PARSE_HDR && !parser_hdr(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_MAT && !parser_mat(parser))
			parser->state = PARSE_ERROR;
		else if (parser->state == PARSE_MAP && !parser_map(parser))
			parser->state = PARSE_ERROR;
		free(parser->line);
		parser->line = get_next_line(parser->fd);
	}
	if (parser->state != PARSE_MAP)
		return (parser_error_file(parser, err(0, "Unexpected end of file")), 0);
	return (parser->state != PARSE_ERROR && parser_validate(parser));
}

bool
	parse_map(const char *file)
{
	struct s_parser	parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.file = file;
	parser.fd = -1;
	parser.s_data.player_orientation = ORI_NONE;
	parser.s_data.colors[0] = (t_color)COLOR_UNINIT;
	parser.s_data.colors[1] = (t_color)COLOR_UNINIT;
	if (ft_strlen(file) < 4 || ft_strncmp(file + ft_strlen(file) - 4, ".cub",
			4))
		return (parser_error(err_style(err_style(err(0, "File '"),
						parser.file, (t_text_style){COL_CYAN, 0, 0}), "' has an"
				" incorrect extension.", (t_text_style){0, 0, 0})),
				parser_free(&parser), false);
	parser.fd = open(parser.file, O_RDONLY);
	if (parser.fd < 0)
		return (parser_error(err(err_style(err(0, "Failed to open file '"),
						parser.file, (t_text_style){COL_CYAN, 0, 0}), "'.")),
		parser_free(&parser), false);
	if (!parse_line(&parser))
		return (parser_free(&parser), false);
	// TODO: Make into map
	parser_free(&parser);
	return (true);
}

void
	parser_free(struct s_parser *parser)
{
	size_t	i;

	free(parser->s_data.textures[0]);
	free(parser->s_data.textures[1]);
	free(parser->s_data.textures[2]);
	free(parser->s_data.textures[3]);
	atlas_mat_free(&parser->s_data.mat_atlas);
	atlas_tex_free(NULL, &parser->s_data.tex_atlas);
	i = 0;
while (i < parser->s_data.lines_size)
		free(parser->s_data.lines[i]);
	free(parser->s_data.lines);
	free(parser->line);
	if (parser->fd != -1)
		close(parser->fd);
}
