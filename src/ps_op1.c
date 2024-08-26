#include "../push_swap.h"

void	ft_iswap(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	ps_op_pa(t_stk *a, t_stk *b)
{
	if (!b->len)
		return;
	stk_push_node(a, stk_pop_node(b));
	(b->len)--;
	(a->len)++;
}

void	ps_op_pb(t_stk *a, t_stk *b)
{
	ps_op_pa(b, a);
}

void	ps_op_sa(t_stk *a, t_stk *b)
{
	if (a->len < 2)
		return ;
	ft_iswap(&(a->head->next->val), &(a->head->val));
}

void	ps_op_sb(t_stk *a, t_stk *b)
{
	ps_op_sa(b, a);
}

void	ps_op_ss(t_stk *a, t_stk *b)
{
	ps_op_sa(a, b);
	ps_op_sa(b, a);
}

void	ps_op_ra(t_stk *a, t_stk *b)
{
	if (a->len < 2)
		return ;
	a->head = a->head->next;
}

void	ps_op_rb(t_stk *a, t_stk *b)
{
	ps_op_ra(b, a);
}

void	ps_op_rr(t_stk *a, t_stk *b)
{
	ps_op_ra(a, b);
	ps_op_ra(b, a);
}

void	ps_op_rra(t_stk *a, t_stk *b)
{
	if (a->len < 2)
		return ;
	a->head = a->head->prev;
}

void	ps_op_rrb(t_stk *a, t_stk *b)
{
	ps_op_rra(b, a);
}

void	ps_op_rrr(t_stk *a, t_stk *b)
{
	ps_op_rra(a, b);
	ps_op_rra(b, a);
}
