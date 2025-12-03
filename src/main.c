#include <stdio.h>
#include <util/util.h>
#include <parser/parser.h>

int main(int ac, char **av)
{
	//t_err_str errs = err_style(0, NULL, (t_text_style){0,0,0});
	//err_free(errs);
	parse_map(av[1]);
	return 0;
}
