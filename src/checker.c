#include "push_swap.h"

bool	is_solution(int *input, int input_len, t_op *moves, int moves_len)
{
	t_stk	stk_a;
	t_stk	stk_b;
	bool	res;

	stks_init(input, input_len, &stk_a, &stk_b);
	stks_execute(moves, moves_len, &stk_a, &stk_b);
	res = stks_is_solved(&stk_a, &stk_b);
	stks_destroy(&stk_a, &stk_b);
	return (res);
}
