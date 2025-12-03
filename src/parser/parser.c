#include <parser/parser.h>
#include <fcntl.h>

void
	parser_error(t_err_str err)
{
	t_err_str	banner;

	banner = err_style("", " ERROR: ", (t_text_style){COL_WHITE, COL_RED,
		STYLE_BOLD});
	printf("%s\n%s\n", banner, err);
	err_free(err);
	err_free(banner);
}

void
	parser_error_loc(const struct s_parser *parser, t_err_str errstr)
{
	const t_text_style	st_num = {COL_YELLOW, COL_NONE, STYLE_BOLD};
	const t_text_style	st_none = {0, 0, 0};
	t_err_str			msg;

	msg = err_style(err_style(err_style(err(err_style(err_style(err_style(
		err_style(err_style(err_style(0, " ERROR: ", (t_text_style){COL_WHITE,
		COL_RED, STYLE_BOLD}), "\nFile ", st_none), parser->file, (t_text_style)
		{COL_CYAN, 0, STYLE_UNDERLINE}), "#", st_num), "64", st_num), ": ",
		st_none), errstr), "\n", st_none), parser->line, (t_text_style){
		COL_MAGENTA, 0, STYLE_ITALIC}), "\n", st_none);
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	err_free(errstr);
	err_free(msg);
}

bool
	parse_map(const char *file)
{
	struct s_parser parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.file = file;
	parser.fd = -1;
	if (ft_strlen(file) < 4 || ft_strncmp(file + ft_strlen(file) - 4, ".cub",
		4))
		return (parser_error(err(err_style(err(0, "File '"),
		parser.file, (t_text_style){COL_CYAN, 0, 0}), "' has an incorrect "
		"extension.")), false);
	parser.fd = open(parser.file, O_RDONLY);
	if (parser.fd < 0)
		return (parser_error(err(err_style(err(0, "Failed to open "
		"file '"), parser.file, (t_text_style){COL_CYAN, 0, 0}), "'.")), false);
	parser.line = get_next_line(parser.fd);
	parser.line_num = 1;
	return (parser_error_loc(&parser, err_style(0, "Invalid token", (t_text_style){COL_GREEN, 0, STYLE_BOLD})), false);
	return (true);
}
