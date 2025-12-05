/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

/** @brief Format leak error message */
static t_err_str
	leak_msg(t_pos pos)
{
	const t_text_style	st_none = (t_text_style){0, 0, 0};
	const t_text_style	st_pos = (t_text_style){COL_RED, 0, STYLE_BOLD};
	t_err_str			msg;
	char				buf[64];

	itoa_buf(buf, pos.x);
	msg = err_style(err(0, "Leak detected at "), "(", st_pos);
	msg = err_style(err_style(msg, buf, st_pos), ", ", st_pos);
	itoa_buf(buf, pos.y);
	msg = err_style(err_style(msg, buf, st_pos), ")", st_pos);
	return (err_style(msg, "", st_none));
}

/**
 * @brief Recursively traverse the map to check for leaks
 *
 * @param parser The parser
 * @param traversed An array to store previously traversed cells
 * @param pos Current position
 * @return `true` if the map contains no leaks from the original position `pos`,
 * `false` otherwise
 */
static bool
	traverse_dfs(const struct s_parser *parser, bool *traversed, t_pos pos)
{
	const t_material	*mat;

	if ((size_t)pos.x >= ft_strlen(parser->s_data.lines[pos.y]) || pos.x < 0
		|| (size_t)pos.y >= parser->s_data.lines_size || pos.y < 0)
		return (parser_error_file(parser, leak_msg(pos)), false);
	if (traversed[pos.x + pos.y * parser->s_data.map_width])
		return (true);
	traversed[pos.x + pos.y * parser->s_data.map_width] = true;
	mat = atlas_mat_get(&parser->s_data.mat_atlas,
			parser->s_data.lines[pos.y][pos.x]);
	if (mat->type == MAT_OPEN)
		return (parser_error_file(parser, leak_msg(pos)), false);
	return (traverse_dfs(parser, traversed, (t_pos){pos.x + 1, pos.y})
		&& traverse_dfs(parser, traversed, (t_pos){pos.x, pos.y + 1})
		&& traverse_dfs(parser, traversed, (t_pos){pos.x - 1, pos.y})
		&& traverse_dfs(parser, traversed, (t_pos){pos.x, pos.y - 1}));
}

bool
	parser_validate(struct s_parser *parser)
{
	bool	*traversed;

	if (parser->s_data.player_orientation == ORI_NONE)
		return (parser_error_file(parser, err(0, "Missing spawn")), false);
	traversed = xmalloc(sizeof(bool) * (size_t)parser->s_data.map_width
			* (size_t)parser->s_data.map_height);
	ft_memset(traversed, 0, sizeof(bool) * (size_t)parser->s_data.map_width
		* (size_t)parser->s_data.map_height);
	traverse_dfs(parser, traversed, parser->s_data.player_spawn);
	free(traversed);
	return (true);
}
