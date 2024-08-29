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

bool	is_sorted(int *parsed, int size)
{
	for (int i = 0; i < size - 1; i++)
		if (parsed[i] > parsed[i+1])
			return false;
	return true;
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

bool	is_stupid(t_op *sol, int curr, int a_len, int b_len)
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
		return(b_len < 0);
	case OP_PB:
		return(a_len < 0);
	default:
		__builtin_unreachable();
	}
}

bool	solve_backtrack_4real(int *parsed, int size, t_op *sol, int max_depth, int curr_depth, int b_len)
{
	if (curr_depth == max_depth)
		return (is_solution(parsed, size, sol, max_depth));

	for (t_op op = 0; op < NB_OP; op++)
	{
		sol[curr_depth] = op;
		if (op == OP_PA) b_len--;
		if (op == OP_PB) b_len+=2;
		if (op == OP_SA) b_len--;
		if (!is_stupid(sol, curr_depth, size - b_len, b_len))
			if (solve_backtrack_4real(parsed, size, sol, max_depth, curr_depth + 1, b_len))
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

	return (solve_backtrack_4real(parsed, size, *sol, depth, 0, 0));
}

void	solve_backtrack(int *parsed, int size)
{
	int		depth;
	t_op	*sol;

	if (is_sorted(parsed, size))
	{
//		ft_printf("Id\n");
//		ft_printf("---------------\n");
		return ;
	}
	depth = 1;

	while (!solve_backtrack_depth(parsed, size, &sol, depth))
	{
		free(sol);
		depth++;
	}
	print_sol(sol, depth);
	free(sol);
}
