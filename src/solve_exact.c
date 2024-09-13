#include "../push_swap.h"

static int	ilog11(long long n)
{
	int res;

	res = 1;
	while (n / 11)
	{
		n /= 11;
		res++;
	}
	return (res);
}

static t_op	*ll_to_op_arr(long long n)
{
	t_op	*res;
	int		len;

	len = ilog11(n);
	res = malloc(len * sizeof(t_op));
	while (len)
	{
		len--;
		res[len] = n % 11;
		n /= 11;
	}
	return (res);
}

void	print_sol(t_op *moves, int moves_len)
{
	int	i;

	i = 0;
	while (i < moves_len)
	{
		ft_printf("%s\n", ps_op_to_str(moves[i]));
		i++;
	}
//	ft_printf("---------------\n");
}

void	solve_brute_force(t_node *nodes, int size)
{
	long long	i;
	t_op		*sol;

	i = 0;
	sol = ll_to_op_arr(i);
	while (!is_solution(nodes, size, sol, ilog11(i)))
	{
		i++;
		free(sol);
		sol = ll_to_op_arr(i);
	}
	print_sol(sol, ilog11(i));
	free(sol);
}

bool	is_stupid(t_op *sol, int curr, int max, int a_len, int b_len)
{
	switch (sol[curr])
	{
	case OP_SA:
		return((curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS))
			|| a_len < 2);
	case OP_SB:
		return((curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS))
			|| b_len < 2);
	case OP_SS:
		return((curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS))
			|| a_len < 2 || b_len < 2);

	case OP_RA:
		return((curr && (sol[curr-1] == OP_RRA || sol[curr-1] == OP_RB || sol[curr-1] == OP_RRR))
			|| a_len < 2);
	case OP_RRA:
		return((curr && (sol[curr-1] == OP_RA || sol[curr-1] == OP_RRB || sol[curr-1] == OP_RR))
			|| a_len < 3);
	case OP_RB:
		return((curr && (sol[curr-1] == OP_RRB || sol[curr-1] == OP_RA || sol[curr-1] == OP_RRR))
			|| b_len < 2);
	case OP_RRB:
		return((curr && (sol[curr-1] == OP_RB || sol[curr-1] == OP_RRA || sol[curr-1] == OP_RR))
			|| b_len < 3);
	case OP_RR:
		return((curr && (sol[curr-1] == OP_RRA || sol[curr-1] == OP_RRB || sol[curr-1] == OP_RRR))
			|| a_len < 2 || b_len < 2);
	case OP_RRR:
		return((curr && (sol[curr-1] == OP_RA || sol[curr-1] == OP_RB || sol[curr-1] == OP_RR))
			|| a_len < 2 || b_len < 2);
	case OP_PA:
		return(b_len < 0 || (curr && sol[curr -1] == OP_PB));
	case OP_PB:
		return(a_len < 0 || b_len >= (max-curr) || (curr && sol[curr -1] == OP_PA));
	default:
		__builtin_unreachable();
	}
}

bool	solve_iddfs_rec(t_node *nodes, int size, t_op *sol, int max_depth, int curr_depth, int b_len)
{
	if (curr_depth == max_depth)
		return (is_solution(nodes, size, sol, max_depth));

	for (t_op op = 0; op < NB_OP; op++)
	{
		sol[curr_depth] = op;
		if (op == OP_PB) b_len++;
		if (op == OP_PA) b_len-=2;
		if (op == OP_SS) b_len++;
		if (!is_stupid(sol, curr_depth, max_depth, size - b_len, b_len))
			if (solve_iddfs_rec(nodes, size, sol, max_depth, curr_depth + 1, b_len))
				return (true);
	}
	sol[curr_depth] = -1;
	return (false);
}
		
void	solve_backtrack(t_node *nodes, int size)
{
	int		depth;
	t_op	sol[32];

	if (is_sorted(nodes, size))
		return ;
	depth = 1;

	while (!solve_iddfs_rec(nodes, size, sol, depth, 0, 0))
		depth++;
	print_sol(sol, depth);
	free(nodes);
}
