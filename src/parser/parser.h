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
# include <assets/assets.h>
# include <map/map.h>

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
	/** @brief Parsing properties */
	PARSE_PROPS,
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
		/** @brief Map horizontal strides */
		char				**lines;
		/** @brief Number of horizontal map strides */
		size_t				lines_size;
		/** @brief Capacity of horizontal map strides */
		size_t				lines_capacity;
		/** @brief Current maximum map width */
		int					map_width;
		/** @brief Current maximum map height */
		int					map_height;
		/** @brief Atlas for textures */
		t_texture_atlas		tex_atlas;
		/** @brief Atlas for materials */
		t_material_atlas	mat_atlas;
		/** @brief Flag to indicate whether custom properties have been
		 * initialized */
		bool				parsing_properties;
		/** @brief Custom properties for the map */
		t_map_props			properties;
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
	enum e_parser_state		state;
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
 * @brief Validate the parsed data
 *
 * @param parser The parser
 * @return `true` if parsed data is valid, `false` otherwise
 */
bool
parser_validate(struct s_parser *parser);
/**
 * @brief Trim a string at its start
 *
 * @param str String to trim
 * @param set Characters to trim
 * @return The first substring of `str` that does not start with a character in
 * `set`
 */
const char
*parser_trim_start(const char *str, const char *set);

/**
 * @brief Expect a space token after another token
 *
 * A space token is any combination of ` ` and `\t`.
 *
 * @param parser The parser
 * @param line Current line position (will be advanced on success)
 * @param after Token to expect a space after (for error messages..)
 * @return `true` on success, `false` on errors
 */
bool
parser_expect_space(
	struct s_parser *parser,
	const char **line,
	const char *after);

/**
 * @defgroup ErrorParsing Parser Errors
 * @ingroup Parser
 * @{
 */

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

/** @} */

/**
 * @defgroup HeaderParsing Header Parsing
 * @ingroup Parser
 * @{
 */

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

/**
 * @defgroup MaterialParsing Material Parsing
 * @ingroup Parser
 * @{
 */

/**
 * @brief Parse a line from the map materials
 *
 * Will advance the parser's state when the header is successfully parsed
 *
 * @param parser The parser
 * @return true on success, false on errors
 */
bool
parser_mat(struct s_parser *parser);
/**
 * @brief Default parser for materials
 *
 * @param parser The parser
 * @return 1 on success, 0 if no materials were parsed, -1 on errors
 */
int
parse_mat_default(struct s_parser *parser);
/**
 * @brief Parse a material
 *
 * @param parser The parser
 * @param ident Identifier for the material
 * @param tex_attrs Textures attributes and names: `{{IDENT1, NAME1}, .., NULL}`
 * @param mat The material
 * @return `1` on success, `0` is not the correct identifier, `-1` on errors
 */
int
parse_material(
	struct s_parser *parser,
	const char *ident,
	const char **tex_attrs,
	t_material *mat);
/**
 * @brief Parse materials textures
 *
 * @param parser The parser
 * @param line Current position in line
 * @param tex_attrs Attributes to parse: `{{IDENT1, NAME1}, .., NULL}`
 * @param mat The material
 * @return `true` on success, `false` on errors
 */
bool
parse_mat_textures(
	struct s_parser *parser,
	const char **line,
	const char **tex_attrs,
	t_material *mat);

/** @} */


/**
 * @defgroup PropertyParsing Property Parsing
 * @ingroup Parser
 * @{
 */

/**
 * @brief Parse a line of properties
 *
 * Will advance the parser's state when the header is successfully parsed
 *
 * @param parser The parser
 * @return true on success, false on errors
 */
bool
parser_props(struct s_parser *parser);

/** @} */

/**
 * @defgroup MapParsing Map Parsing
 * @ingroup Parser
 * @{
 */

/**
 * @brief Parse a line from the map content
 *
 * Will advance the parser's state when the header is successfully parsed
 *
 * @param parser The parser
 * @return true on success, false on errors
 */
bool
parser_map(struct s_parser *parser);

/** @} */

/** @} */

#endif // PARSER_H
