/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgamba <linogamba@pundalik.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 05:57:40 by lgamba            #+#    #+#             */
/*   Updated: 2025/12/04 05:57:40 by lgamba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "util.h"

/** @brief Gets the currently active style on a file descriptor */
static struct s_text_style
	*style_opt(int fd)
{
	static struct s_text_style	styles[2];

	if (fd != 1 && fd != 2)
		return (NULL);
	return (&styles[fd - 1]);
}

/** @brief Applies color on a file descriptor */
static bool
	set_color(
	int fd,
	bool bg,
	enum e_text_colors color,
	struct s_text_style *active)
{
	enum e_text_colors	*current;
	char				buf[5];

	current = &active->fg;
	if (bg)
		current = &active->bg;
	if (*current == color)
		return (true);
	*current = color;
	ft_memcpy(buf, "\033[??m", 5);
	buf[2] = "34"[bg];
	buf[3] = (char)(color - 1) + '0';
	return (write(fd, buf, 5) == 5);
}

/** @brief Applies text style on a file descriptor */
static bool
	set_style(
	int fd,
	enum e_text_style style,
	struct s_text_style *active)
{
	char				buf[64];
	size_t				n;
	size_t				i;
	static unsigned int	styles[][2] = {{STYLE_ITALIC, 3}, {STYLE_UNDERLINE, 4},
	{STYLE_BOLD, 1}};

	if (active->style == style)
		return (true);
	active->style = style;
	if (style == STYLE_RESET)
	{
		*active = (struct s_text_style){0, 0, STYLE_RESET};
		return (write(fd, "\033[0m", 4) == 4);
	}
	n = 0;
	i = 0;
	while (i++ < 3)
	{
		if (!(style & styles[i - 1][0]))
			continue ;
		ft_memcpy(buf + n, "\033[?m", 4);
		buf[2] = (char)styles[i - 1][1] + '0';
		n += 4;
	}
	return (write(fd, buf, n) == (ssize_t)n);
}

bool
	style(int fd,
	enum e_text_colors fg,
	enum e_text_colors bg,
	enum e_text_style style)
{
	struct s_text_style *const	active = style_opt(fd);

	if (!active)
		return (false);
	if (!set_style(fd, style, active))
		return (false);
	if (active->style == STYLE_RESET)
	{
		active->style = STYLE_NONE;
		return (true);
	}
	return (set_color(fd, true, bg, active)
		&& set_color(fd, false, fg, active));
}
