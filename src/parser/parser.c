#include <parser/parser.h>
#include <fcntl.h>

int
	parse_map(const char *file)
{
	struct s_parser parser;

	ft_memset(&parser, 0, sizeof(parser));
	parser.file = file;
	parser.fd = open(parser.file, O_RDONLY);
	if (parser.fd < 0)
		parser_error(err(err(err("", "Failed to open file '"), parser.file), "'."));
}
