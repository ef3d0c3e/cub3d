#include <util/util.h>

static void
	format_colors(
	char *buf,
	struct s_text_style style,
	struct s_text_style *active)
{
	size_t				n;

	n = 0;
	if (active->bg != style.bg)
	{
		active->bg = style.bg;
		ft_memcpy(buf + n, "\033[4?m", 5);
		buf[n + 3] = (char)(style.bg - 1) + '0';
		n += 5;
	}
	if (active->fg != style.fg)
	{
		active->fg = style.fg;
		ft_memcpy(buf + n, "\033[3?m", 5);
		buf[n + 3] = (char)(style.fg - 1) + '0';
		n += 5;
	}
	buf[n] = 0;
}

static void
	format_style(
	char *buf,
	t_text_style style,
	t_text_style *active)
{
	size_t				n;
	size_t				i;
	static unsigned int	styles[][2] = {{STYLE_ITALIC, 3}, {STYLE_UNDERLINE, 4},
	{STYLE_BOLD, 1}};

	if (!ft_memcmp(active, &style, sizeof(style)))
		return ;
	active->style = style.style;
	if (style.style == STYLE_RESET)
	{
		*active = (struct s_text_style){0, 0, STYLE_RESET};
		ft_memcpy(buf, "\033[0m", 4);
		return ;
	}
	n = 0;
	i = 0;
	while (i++ < 3)
	{
		if (!(style.style & styles[i - 1][0]))
			continue ;
		ft_memcpy(buf + n, "\033[?m", 4);
		buf[n + 2] = (char)styles[i - 1][1] + '0';
		n += 4;
	}
	format_colors(buf + n, style, active);
}

t_err_str
	err_style(t_err_str errstr,
	const char *str,
	t_text_style style)
{
	t_text_style	*active;
	char			buf[128];

	if (!errstr)
		errstr = err(0, "");
	active = &err_hdr(errstr)->style;
	buf[0] = 0;
	format_style(buf, style, active);
	if (buf[0])
		return (err(err(err(errstr, "\033[0m"), buf), str));
	else
		return (err(err(errstr, buf), str));
}
