/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser/parser.h>

void
	parser_error(t_err_str errstr)
{
	const t_text_style	st_none = {0, 0, 0};
	t_err_str			msg;

	msg = err_style(err(err_style(err_style(0, " ERROR: ", (t_text_style){COL_WHITE, COL_RED,
						STYLE_BOLD}), "\n", st_none), errstr), "\n", st_none);
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}

void
	parser_error_loc(const struct s_parser *parser, t_err_str errstr)
{
	const t_text_style	st_num = {COL_YELLOW, COL_NONE, STYLE_BOLD};
	const t_text_style	st_none = {0, 0, 0};
	t_err_str			msg;
	char				line_n[64];

	itoa_buf(line_n, parser->line_num);
	msg = err_style(err_style(err_style(err(err_style(err_style(err_style(
									err_style(err_style(err_style(0, " ERROR: ",
												(t_text_style){COL_WHITE,
												COL_RED, STYLE_BOLD}), "\nFile "
											"", st_none), parser->file,
										(t_text_style){COL_CYAN, 0,
										STYLE_UNDERLINE}), "#", st_num), line_n,
								st_num), ": ", st_none), errstr), "\n", st_none
					), parser->line, (t_text_style){COL_MAGENTA, 0,
				STYLE_ITALIC}), "", st_none);
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}

void
	parser_error_file(const struct s_parser *parser, t_err_str errstr)
{
	const t_text_style	st_none = {0, 0, 0};
	t_err_str			msg;

	msg = err_style(err_style(err(err_style(err_style(err_style(err_style(0,
									" ERROR: ", (t_text_style){COL_WHITE,
									COL_RED, STYLE_BOLD}), "\nFile ", st_none),
							parser->file, (t_text_style){COL_CYAN, 0,
							STYLE_UNDERLINE}), ": ", st_none), errstr), "\n",
				st_none), "", st_none);
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}
