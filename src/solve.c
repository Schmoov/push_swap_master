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
}

void	solve_brute_force(int *parsed, int size)
{
	long long	i;
	t_op		*sol;

	i = 0;
	sol = ll_to_op_arr(i);
	while (!is_solution(parsed, size, sol, ilog11(i)))
	{
		i++;
		free(sol);
		sol = ll_to_op_arr(i);
	}
	print_sol(sol, ilog11(i));
	free(sol);
}

bool	is_pa_stupid(t_op *sol, int curr)
{
	int count = 0;

	for (int i = 0; i < curr; i++)
	{
		if (sol[i] == OP_PB)
			count++;
		if (sol[i] == OP_PA)
			count--;
	}
	return (count <= 0);
}

bool	is_stupid(t_op *sol, int curr)
{
	switch (sol[curr])
	{
	case OP_SA:
		return(curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS));
	case OP_SB:
		return(curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS));
	case OP_SS:
		return(curr && (sol[curr-1] == OP_SA || sol[curr-1] == OP_SB || sol[curr-1] == OP_SS));

	case OP_RA:
		return(curr && (sol[curr-1] == OP_RRA || sol[curr-1] == OP_RB || sol[curr-1] == OP_RRR));
	case OP_RRA:
		return(curr && (sol[curr-1] == OP_RA || sol[curr-1] == OP_RRB || sol[curr-1] == OP_RR));
	case OP_RB:
		return(curr && (sol[curr-1] == OP_RRB || sol[curr-1] == OP_RA || sol[curr-1] == OP_RRR));
	case OP_RRB:
		return(curr && (sol[curr-1] == OP_RB || sol[curr-1] == OP_RRA || sol[curr-1] == OP_RR));
	case OP_RR:
		return(curr && (sol[curr-1] == OP_RRA || sol[curr-1] == OP_RRB || sol[curr-1] == OP_RRR));
	case OP_RRR:
		return(curr && (sol[curr-1] == OP_RA || sol[curr-1] == OP_RB || sol[curr-1] == OP_RR));
	case OP_PA:
		return(is_pa_stupid(sol, curr));
	default:
		return (false);
	}
}

bool	solve_backtrack_4real(int *parsed, int size, t_op *sol, int max_depth, int curr_depth)
{
	if (curr_depth == max_depth)
		return (is_solution(parsed, size, sol, max_depth));

	for (t_op op = 0; op < NB_OP; op++)
	{
		sol[curr_depth] = op;
		if (!is_stupid(sol, curr_depth))
			if (solve_backtrack_4real(parsed, size, sol, max_depth, curr_depth + 1))
				return (true);
	}
	sol[curr_depth] = -1;
	return (false);
}
		

bool	solve_backtrack_depth(int *parsed, int size, t_op **sol, int depth)
{
	*sol = malloc(depth * sizeof(t_op));
	for (int i = 0; i < depth; i++)
		(*sol)[i] = -1;

	return (solve_backtrack_4real(parsed, size, *sol, depth, 0));
}

void	solve_backtrack(int *parsed, int size)
{
	int		depth;
	t_op	*sol;

	depth = 1;

	while (!solve_backtrack_depth(parsed, size, &sol, depth))
	{
		free(sol);
		depth++;
	}
	print_sol(sol, depth);
	free(sol);
}
