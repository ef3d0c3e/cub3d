#ifndef PARSER_H
# define PARSER_H

# include <util/util.h>
# include <stdlib.h>
 
/** @brief The parser */
struct s_parser
{
	/** @brief Parsed data */
	struct
	{
		/** @brief Default wall textures path */
		char	*textures[4];
		/** @brief Default ceiling color */
		t_color	color_ceil;
		/** @brief Default floor color */
		t_color	color_floor;
		/** @brief Player spawn */
		t_pos	player_spawn;
		/** @brief Map vertical strides */
		char	**lines;
		/** @brief Number of vertical map strides */
		size_t	lines_size;
		/** @brief Capacity of vertical map strides */
		size_t	lines_capacity;
		/** @brief Current maximum map width */
		int		map_width;
		/** @brief Current maximum map height */
		int		map_height;
	}	s_data;

	/** @brief Parsed file */
	const char *file;
	/** @brief File descriptor of the parsed file */
	int			fd;

	/** @brief Current line */
	char *line;
	/** @brief Current line number */
	size_t line_num;
};

bool
parse_map(const char *file);


////////////////////////////////////////////////////////////////////////////////
// Internal                                                                   //
////////////////////////////////////////////////////////////////////////////////

void
parser_error(t_err_str err);
void
parser_error_loc(const struct s_parser *parser, t_err_str err);

#endif // PARSER_H
