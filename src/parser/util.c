/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <parser/parser.h>

const char
	*parser_trim_start(const char *str, const char *set)
{
	while (*str && ft_strchr(set, *str))
		++str;
	return (str);
}

bool
	parser_expect_space(
	struct s_parser *parser,
	const char **line,
	const char *after)
{
	const size_t	after_len = ft_strlen(after);
	const char		*advanced = parser_trim_start(*line + after_len, " \t");

	if (advanced != *line + after_len)
	{
		*line = advanced;
		return (true);
	}
	parser_error_loc(parser, err_style(err_style(err(0, "Expected a space after"
					" '"), after, (t_text_style){COL_YELLOW, 0, STYLE_BOLD}),
			"'", (t_text_style){0, 0, 0}));
	return (false);
}
