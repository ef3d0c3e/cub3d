#ifndef UTIL_H
# define UTIL_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <mlx_int.h>

# include <libft.h>
# include <get_next_line.h>

////////////////////////////////////////////////////////////////////////////////
// Text style                                                                 //
////////////////////////////////////////////////////////////////////////////////

/** @brief Colors for the text */
enum e_text_colors
{
	COL_NONE = 0,
	COL_BLACK,
	COL_RED,
	COL_GREEN,
	COL_YELLOW,
	COL_BLUE,
	COL_MAGENTA,
	COL_CYAN,
	COL_WHITE,
};

/** @brief Styles for the text */
enum e_text_style
{
	STYLE_NONE = 0x00,
	STYLE_UNDERLINE = 0x01,
	STYLE_BOLD = 0x02,
	STYLE_ITALIC = 0x04,
	STYLE_RESET = 0x10,
};

/** @brief Internal bookkeeping struct */
typedef struct s_text_style
{
	enum e_text_colors	fg;
	enum e_text_colors	bg;
	enum e_text_style	style;
}	t_text_style;

/**
 * @brief Sets the style globally on a file descriptor
 *
 * @param fd The destination file descriptor (1 or 2)
 * @param fg The foreground color
 * @param bg The background color
 * @param style The style
 *
 */
bool
style(int fd,
	enum e_text_colors fg,
	enum e_text_colors bg,
	enum e_text_style style);

////////////////////////////////////////////////////////////////////////////////
// Definitions                                                                //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_vec2
{
	float x;
	float y;
}	t_vec2;

typedef struct s_pos
{
	int x;
	int y;
}	t_pos;

typedef uint32_t t_color;

////////////////////////////////////////////////////////////////////////////////
// String utils                                                               //
////////////////////////////////////////////////////////////////////////////////

typedef char* t_err_str;

/** @brief Hidden header for the header string */
struct s_err_str_hdr
{
	/** @brief String size */
	size_t			size;
	/** @brief String capacity */
	size_t			capacity;
	/** @brief Current active style */
	t_text_style	style;
};

t_err_str
err(t_err_str err, const char *str);

t_err_str
err_style(t_err_str errstr,
	const char *str,
	t_text_style style);

void
err_free(t_err_str err);

/** @brief Get the header for an error */
struct s_err_str_hdr
*err_hdr(t_err_str err);

////////////////////////////////////////////////////////////////////////////////
// Memory utils                                                               //
////////////////////////////////////////////////////////////////////////////////


void
*xmalloc(size_t size);

void
*xrealloc(void *ptr, size_t oldsz, size_t newsz);

#endif // UTIL_H
