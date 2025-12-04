/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include <util/util.h>
# include <stdlib.h>

/**
 * @defgroup Parser Parser
 * @{
 */

/** @brief State of the parser */
enum e_parser_state
{
	/** @brief Parsing header */
	PARSE_HDR = 0,
	/** @brief Parsing materials */
	PARSE_MAT,
	/** @brief Parsing entities */
	PARSE_ENT,
	/** @brief Parsing map */
	PARSE_MAP,
	/** @brief An error happened */
	PARSE_ERROR,
};

/** @brief The parser */
struct s_parser
{
	/** @brief Parsed data */
	struct
	{
		/** @brief Default wall textures path */
		char			*textures[4];
		/** @brief Default ceiling color */
		t_color			color_ceil;
		/** @brief Default floor color */
		t_color			color_floor;
		/** @brief Player spawn */
		t_pos			player_spawn;
		/** @brief Map vertical strides */
		char			**lines;
		/** @brief Number of vertical map strides */
		size_t			lines_size;
		/** @brief Capacity of vertical map strides */
		size_t			lines_capacity;
		/** @brief Current maximum map width */
		int				map_width;
		/** @brief Current maximum map height */
		int				map_height;
	}					s_data;

	/** @brief Parsed file */
	const char			*file;
	/** @brief File descriptor of the parsed file */
	int					fd;

	/** @brief Current line */
	char				*line;
	/** @brief Current line number */
	int					line_num;

	/** @brief Parser state */
	enum e_parser_state	state;
};

/**
 * @brief Parses the map provided by a file
 *
 * @param file Map path
 * @return `true` on success, `false` on failures
 */
bool
parse_map(const char *file);


////////////////////////////////////////////////////////////////////////////////
// Internal                                                                   //
////////////////////////////////////////////////////////////////////////////////

/**
 * @internal
 * @brief Displays a general parser error
 *
 * @param err The error message
 * @relatesalso s_parser
 */
void
parser_error(t_err_str err);
/**
 * @brief Displays a parser error alongside the location of the error
 *
 * @param parser The parser
 * @param err The error message
 * @relatesalso s_parser
 */
void
parser_error_loc(const struct s_parser *parser, t_err_str err);

const char
*parser_trim_start(const char *str, const char *set);

/**
 * @}
 */

#endif // PARSER_H
