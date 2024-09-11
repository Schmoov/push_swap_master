#include "../push_swap.h"

int	main(int argc, char **argv)
{
	int		*input;
	t_node	*nodes;

	input = parse_and_compress(argv + 1, argc - 1);
	nodes = parsed_to_nodes(input, argc - 1);
	solve_backtrack(nodes, argc - 1);
	free(input);
}
