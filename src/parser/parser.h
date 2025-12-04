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
	/** @brief Parsing the header */
	PARSE_HDR = 0,
	/** @brief Parsing materials */
	PARSE_MAT,
	/** @brief Parsing entities */
	PARSE_ENT,
	/** @brief Parsing the map */
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
		char				*textures[4];
		/** @brief Default color for floor/ceiling */
		t_color				colors[2];
		/** @brief Player spawn */
		t_pos				player_spawn;
		/** @brief Player orientation */
		enum e_orientation	player_orientation;
		/** @brief Map vertical strides */
		char				**lines;
		/** @brief Number of vertical map strides */
		size_t				lines_size;
		/** @brief Capacity of vertical map strides */
		size_t				lines_capacity;
		/** @brief Current maximum map width */
		int					map_width;
		/** @brief Current maximum map height */
		int					map_height;
	}						s_data;
	/** @brief Parsed file */
	const char				*file;
	/** @brief File descriptor of the parsed file */
	int						fd;
	/** @brief Current line */
	char					*line;
	/** @brief Current line number */
	int						line_num;

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
 * @brief Free the parser
 *
 * @param parser The parser
 */
void
parser_free(struct s_parser *parser);

/**
 * @brief Display a general parser error
 *
 * @param err The error message
 * @relatesalso s_parser
 */
void
parser_error(t_err_str err);
/**
 * @brief Display a parser error alongside the location of the error
 *
 * @param parser The parser
 * @param err The error message
 * @relatesalso s_parser
 */
void
parser_error_loc(const struct s_parser *parser, t_err_str err);
/**
 * @brief Display a parser error alongside the file of the error
 *
 * @param parser The parser
 * @param err The error message
 * @relatesalso s_parser
 */
void
parser_error_file(const struct s_parser *parser, t_err_str err);

const char
*parser_trim_start(const char *str, const char *set);

/* --- Header parsing --- */

/**
 * @brief Parse a line from the header
 *
 * Will advance the parser's state when the header is successfully parsed
 *
 * @param parser The parser
 * @return true on success, false on errors
 */
bool
parser_hdr(struct s_parser *parser);

/**
 * @brief Get the identifier and display name of a header field
 *
 * @param id Field id (0-4 for textures, 0-1 for colors)
 * @param is_color true if the field is a color, false for textures
 * @return An array containing {IDENTIFIER, DISPLAYNAME} for the field
 */
const char
**parser_hdr_fields(size_t id, bool is_color);

/**
 * @brief Attempt to parse a texture with orientation in the header
 *
 * @param parser The parser
 * @param line Trimmed line
 * @return 0 if the current line doesn't contain a texture, 1 on success and -1
 * if an error happened
 */
int
parse_hdr_texture(struct s_parser *parser, const char *line);

/**
 * @brief Attempt to parse a color in the header
 *
 * @param parser The parser
 * @param line Trimmed line
 * @return 0 if the current line doesn't contain a color, 1 on success and -1
 * if an error happened
 */
int
parse_hdr_color(struct s_parser *parser, const char *line);

/** @} */

#endif // PARSER_H
