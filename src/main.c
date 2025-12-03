#include <stdio.h>
#include <util/util.h>

int main(int ac, char **av)
{
	style(1, COL_WHITE, COL_RED, STYLE_BOLD);
	printf(" ERROR: \n");
	style(1, 0, 0, STYLE_RESET);
	printf("Test 123\n");
	return 0;
}
