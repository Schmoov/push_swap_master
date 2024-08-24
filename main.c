#include "push_swap.h"

void	parse(t_stk *stk, char **nums, int size)
{
	int	i;

	i = size - 1;
	while (i > -1)
	{
		stk_push_node(stk, node_create(atoi(nums[i])));
		i--;
	}
}

void	print_state(t_stk *stk_a, t_stk *stk_b)
{
	for 
int main(int argc, char **argv)
{
	t_stk	stk_a;
	t_stk	stk_b;

	memset(stk_a, 0, sizeof(t_stk));
	memset(stk_b, 0, sizeof(t_stk));
	parse(&stk_a, argv + 1, argc - 1);
}
