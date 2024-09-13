#include "../push_swap.h"

void	solve_big_divide(t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int	len;

	while (a->len > 2)
	{
		i = 0;
		len = a->len;
		while (i < len)
		{
			if (a->head->val >= 3 * len / 4)
			{
				ps_op_pb(a,b);
				sol_append_one(sol, OP_PB);
			}
			else if (a->head->val >= len / 2)
			{
				ps_op_pb(a,b);
				ps_op_rb(a,b);
				sol_append_one(sol, OP_PB);
				sol_append_one(sol, OP_RB);
			}
			else
			{
				ps_op_ra(a,b);
				sol_append_one(sol, OP_RA);
			}
			i++;
		}
	}
	if (a->head->val)
	{
		ps_op_sa(a,b);
		sol_append_one(sol, OP_SA);
	}
}

void	solve_big_merge(t_stk *a, t_stk *b, t_sol *sol)
{
	int	pos;

	while (b->len)
	{
		for (int i = 0; i < b->len; i++)
		{
			if (b->head->val == a->len)
				pos = i;
			ps_op_rb(a,b);
		}
		if (pos <= b->len / 2)
		{
			for (int i = 0; i < pos; i++)
			{
				ps_op_rb(a,b);
				sol_append_one(sol, OP_RB);
			}
		}
		else
		{
			for (int i = 0; i < b->len - pos; i++)
			{
				ps_op_rrb(a,b);
				sol_append_one(sol, OP_RRB);
			}
		}
		ps_op_pa(a,b);
		ps_op_ra(a,b);
		sol_append_one(sol, OP_PA);
		sol_append_one(sol, OP_RA);
	}
}

t_sol	solve_big(t_node *parsed, int size)
{
	t_stk	stk_a;
	t_stk	stk_b;
	t_sol	sol;

	sol_init(&sol);
	stks_init(parsed, size, &stk_a, &stk_b);
	solve_big_divide(&stk_a, &stk_b, &sol);
	solve_big_merge(&stk_a, &stk_b, &sol);
	return (sol);
}
