#include "../push_swap.h"


void	solve_big_divide(t_stk *a, t_stk *b, t_sol *sol)
{
	int	i;
	int	lo;
	int	mid;
	int	rb_debt = 0;

	while (a->len > 2)
	{
		i = 0;
		int len = a->len;
		lo = b->len + a->len / 4 ;
		mid = b->len + a->len / 2 ;
		while (i < len)
		{
			if (a->head->val <= lo)
			{
				while (rb_debt)
				{
					ps_op_rb(a,b);
					sol_append_one(sol, OP_RB);
					rb_debt--;
				}
				ps_op_pb(a,b);
				sol_append_one(sol, OP_PB);
			}
			else if (a->head->val <= mid)
			{
				ps_op_pb(a,b);
				sol_append_one(sol, OP_PB);
				rb_debt++;
			}
			else
			{
				if (rb_debt)
				{
					ps_op_rr(a,b);
					sol_append_one(sol, OP_RR);
					rb_debt--;
				}
				else
				{
					ps_op_ra(a,b);
					sol_append_one(sol, OP_RA);
				}
			}
			i++;
		}
	}
}

int		insert_cost(int pos, t_stk *a, t_stk *b)
{
	int res = (pos <= b->len - pos ? pos : b->len - pos);
	int posA = -1;
	int posMin;
	int val = b->head->val;
	int size = a->len + b->len;
	if (3*a->len <= b->len && val <= (3*size)/4) return INT_MAX;
	if (a->len <= b->len && val <= size/2) return INT_MAX;
	if (a->len <= 3*b->len && val <= size/4) return INT_MAX;

	for (int i = 0; i < a->len; i++)
	{
		if (posA == -1 && a->head->val > val && a->head->prev->val < val)
			posA = i;
		if (a->head->val < a->head->prev->val)
			posMin = i;
		ps_op_ra(a,b);
	}
	if (posA == -1) posA = posMin;
	if (a->len - posA < posA) posA = a->len - posA;
	res += posA;
	return (res);
}

void	fast_insert(int pos, t_stk *a, t_stk *b, t_sol *sol)
{

	int val;
	if (pos <= b->len - pos)
	{
		for (int i = 0; i < pos; i++)
		{
			ps_op_rb(a,b);
		}
		val = b->head->val;
		for (int i = 0; i < pos; i++)
		{
			ps_op_rrb(a,b);
		}
	}
	else
	{
		for (int i = 0; i < b->len - pos; i++)
		{
			ps_op_rrb(a,b);
		}
		val = b->head->val;
		for (int i = 0; i < pos; i++)
		{
			ps_op_rb(a,b);
		}
	}
	int rb_debt = ((pos<= b->len-pos) ?pos:pos-b->len);

	int posA = -1;
	int posMin;
	for (int i = 0; i < a->len; i++)
	{
		if (posA == -1 && a->head->val > val && a->head->prev->val < val)
			posA = i;
		if (a->head->val < a->head->prev->val)
			posMin = i;
		ps_op_ra(a,b);
	}
	if (posA == -1) posA = posMin;
	if (posA <= a->len - posA)
	{
		while (rb_debt < 0)
		{
			ps_op_rrb(a,b);
			sol_append_one(sol, OP_RRB);
			rb_debt++;
		}
		for (int i = 0; i < posA; i++)
		{
			if (rb_debt)
			{
				ps_op_rr(a,b);
				sol_append_one(sol, OP_RR);
				rb_debt--;
			}
			else
			{
				ps_op_ra(a,b);
				sol_append_one(sol, OP_RA);
			}
		}
		while (rb_debt)
		{
			ps_op_rb(a,b);
			sol_append_one(sol, OP_RB);
			rb_debt--;
		}
	}
	else
	{
		while (rb_debt>0)
		{
			ps_op_rb(a,b);
			sol_append_one(sol, OP_RB);
			rb_debt--;
		}
		for (int i = 0; i < a->len - posA; i++)
		{
			if (rb_debt)
			{
				ps_op_rrr(a,b);
				sol_append_one(sol, OP_RRR);
				rb_debt++;
			}
			else
			{
				ps_op_rra(a,b);
				sol_append_one(sol, OP_RRA);
			}
		}
		while (rb_debt)
		{
			ps_op_rrb(a,b);
			sol_append_one(sol, OP_RRB);
			rb_debt++;
		}
	}
	ps_op_pa(a,b);
	sol_append_one(sol, OP_PA);
}

void	solve_big_merge(t_stk *a, t_stk *b, t_sol *sol)
{
	while (a->len < 2)
	{
		ps_op_pa(a,b);
		sol_append_one(sol, OP_PA);
	}
	while (b->len)
	{
		int	pos;
		int best = INT_MAX;
		for (int i = 0; i < b->len; i++)
		{
			int cost = insert_cost(i, a, b);
			if (cost < best)
			{
				pos = i;
				best = cost;
			}
			ps_op_rb(a,b);
		}
		fast_insert(pos, a, b, sol);
	}
}

void	solve_big_last_rot(t_stk *a, t_stk *b, t_sol *sol)
{
	while (a->head->val)
	{
		if (a->head->val < a->len / 2)
		{
			ps_op_rra(a,b);
			sol_append_one(sol, OP_RRA);
		}
		else
		{
			ps_op_ra(a,b);
			sol_append_one(sol, OP_RA);
		}
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
	solve_big_last_rot(&stk_a, &stk_b, &sol);
	return (sol);
}
