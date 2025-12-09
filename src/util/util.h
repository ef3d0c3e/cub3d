/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef UTIL_H
# define UTIL_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# include <mlx_int.h>
# include <mlx.h>
# include <libft.h>
# include <get_next_line.h>

# include <util/rbtree/rbtree.h>

////////////////////////////////////////////////////////////////////////////////
// Definitions                                                                //
////////////////////////////////////////////////////////////////////////////////

/** @brief A 2D float vector */
typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

/** @brief A 2D int vector */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

/** @brief Represent orientation (clockwise) */
enum e_orientation
{
	/** @brief No oritnation */
	ORI_NONE = -1,
	/** @brief Facing North */
	ORI_NORTH,
	/** @brief Facing East */
	ORI_EAST,
	/** @brief Facing South */
	ORI_SOUTH,
	/** @brief Facing West */
	ORI_WEST,
};

/** @brief Color type */
typedef uint32_t	t_color;

/**
 * @brief Interpolate between two colors
 *
 * @param x First color
 * @param y Second color
 * @param f Interpolate factor
 * @return `x * f / 255 + y * (1 - f / 255)`
 */
t_color
color_lerp8(t_color x, t_color y, uint8_t f);
/**
 * @brief Interpolate between two colors
 *
 * @param x First color
 * @param y Second color
 * @param f Interpolate factor
 * @return `x * f + y * (1 - f)`
 */
t_color
color_lerp(t_color x, t_color y, float f);
/**
 * @brief Compute the tint of two colors
 *
 * @param x First color
 * @param y Second color
 * @return `x * y`
 */
t_color
color_tint(t_color x, t_color y);

enum
{
	/** @brief Uninitialized color value */
	COLOR_UNINIT = ~0
};

////////////////////////////////////////////////////////////////////////////////
// Text style                                                                 //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup TextStyle Text Styling
 * @{
 */

/** @brief Colors for text */
enum e_text_colors
{
	/** @brief No color (keeps the current active colorf) */
	COL_NONE = 0,
	/** @brief Black */
	COL_BLACK,
	/** @brief Red */
	COL_RED,
	/** @brief Green */
	COL_GREEN,
	/** @brief Yellow */
	COL_YELLOW,
	/** @brief Blue */
	COL_BLUE,
	/** @brief Magenta */
	COL_MAGENTA,
	/** @brief Cyan */
	COL_CYAN,
	/** @brief White */
	COL_WHITE,
};

/** @brief Styles for text */
enum e_text_style
{
	/** @brief No style (keeps the current active style) */
	STYLE_NONE = 0x00,
	/** @brief Underline */
	STYLE_UNDERLINE = 0x01,
	/** @brief Bold */
	STYLE_BOLD = 0x02,
	/** @brief Italic */
	STYLE_ITALIC = 0x04,
	/** @brief Resets style and colors */
	STYLE_RESET = 0x10,
};

/** @brief Represent text style */
typedef struct s_text_style
{
	/** @brief Foreground color */
	enum e_text_colors	fg;
	/** @brief Background color */
	enum e_text_colors	bg;
	/** @brief Text style attributes */
	enum e_text_style	style;
}	t_text_style;

/**
 * @brief Set the style globally on a file descriptor
 *
 * @param fd The destination file descriptor (1 or 2)
 * @param fg The foreground color
 * @param bg The background color
 * @param style The style
 */
bool
style(int fd,
	enum e_text_colors fg,
	enum e_text_colors bg,
	enum e_text_style style);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Error messages                                                             //
////////////////////////////////////////////////////////////////////////////////

/**
 * @defgroup ErrorMessageBuilder Error Messages Builder
 * @{
 */

/**
 * @brief Type for representing error messages
 *
 * @warning Never pass this to `free()` directly. Instead call @ref err_free.
 */
typedef char		*t_err_str;

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

/**
 * @brief Append a string to the error
 *
 * @param err The base error message (can be NULL)
 * @param str String to append to err
 * @return The result of concatenation
 */
t_err_str
err(t_err_str err, const char *str);
/**
 * @brief Append a string to the error
 *
 * @param err The base error message (can be NULL)
 * @param str String to append to err
 * @param n Maximum length of `str`
 * @return The result of concatenation
 */
t_err_str
err_n(t_err_str err, const char *str, size_t n);
/**
 * @brief Append a string to the error with style formatting
 *
 * @param errstr The base error message (can be NULL)
 * @param str String to append to err
 * @param style The custom text styling to apply on the appended string
 * @return The result of concatenation
 */
t_err_str
err_style(t_err_str errstr,
	const char *str,
	t_text_style style);
/**
 * @brief Append a string to the error with style formatting
 *
 * @param errstr The base error message (can be NULL)
 * @param str String to append to err
 * @param n Maximum length of `str`
 * @param style The custom text styling to apply on the appended string
 * @return The result of concatenation
 */
t_err_str
err_style_n(t_err_str errstr,
	const char *str,
	size_t n,
	t_text_style style);
/**
 * @brief Free an error message
 *
 * @param err The error message to free
 */
void
err_free(t_err_str err);

/**
 * @brief Get the header from a valid error string
 *
 * @returns The header of the error string
 */
struct s_err_str_hdr
*err_hdr(t_err_str err);

/** @} */

////////////////////////////////////////////////////////////////////////////////
// Memory utils                                                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocate by calling `malloc` and `exit(1)` on errors
 *
 * @note If `size == 0`, then allocation is performed with `size = 1`.
 * This guarantees unique pointers that can be passed to free.
 *
 * @param size Number of bytes to allocate
 */
void
*xmalloc(size_t size);

/**
 * @brief Reallocate by calling `malloc`, `ft_memcpy` and `exit(1)` on errors
 *
 * @note If @p ptr is `NULL`, this is equivalent to `xmalloc(newsz)`
 * @note If @p newsz is `0`, this is equivalent to `free(newsz)`
 *
 * @param ptr Pointer to reallocate
 * @param oldsz Current size of ptr
 * @param newsz Size of the returned buffer
 *
 * @returns A buffer containing the first @p oldsz of @p ptr and can hold at
 * least @p newsz bytes.
 */
void
*xrealloc(void *ptr, size_t oldsz, size_t newsz);

////////////////////////////////////////////////////////////////////////////////
// Misc utils                                                               //
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Format an integer into a string buffer
 *
 * @param buf Buffer to format into (must be able to hold at least 12
 * characters)
 * @param x Integer to format
 *
 * @returns @p buf
 */
char
*itoa_buf(char *buf, int x);
/**
 * @brief Compare string `a` against string `b`
 *
 * @param a First string
 * @param b Second string
 *
 * @returns `a[i] - b[i]` where `i` is the first byte where `a != b`
 * If `a == b`, then this function returns `0`
 */
int
ft_strcmp(const char *a, const char *b);
/**
 * @brief Copy `n` bytes of `str` into a newly allocated string
 *
 * @param str The string to copy from
 * @param n The number of bytes of `str` to copy

 * @returns The newly created string
 */
char
*ft_strndup(const char *str, size_t n);
/**
 * @brief Strnlen implementation
 *
 * @param str String
 * @param n Maximum length of `str`
 * @return The length of `str` <= `n`
 */
size_t
ft_strnlen(const char *str, size_t n);
/**
 * @brief Clamp an integer value
 *
 * @param value Value to clamp
 * @param min Minimum value
 * @param max Maximum value
 * @return `value` clamped between `min` and `max`
 */
int
clamp(int value, int min, int max);
/**
 * @brief Clamp a floating point value
 *
 * @param value Value to clamp
 * @param min Minimum value
 * @param max Maximum value
 * @return `value` clamped between `min` and `max`
 */
float
clampf(float value, float min, float max);
/**
 * @brief Return the maximum of two floating point values
 *
 * @param a First value
 * @param b Second value
 * @return `a` if `a >= b`, otherwise `b`
 */
float
maxf(float a, float b);

#endif // UTIL_H
