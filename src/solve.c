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
