#include "../push_swap.h"

int	main(int argc, char **argv)
{
	int	*input;

	input = parse_and_compress(argv + 1, argc - 1);
	solve_brute_force(input, argc - 1);
	free(input);
}
