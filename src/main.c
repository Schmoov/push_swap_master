#include "push_swap.h"


static bool	is_int(long long n)
{
	return (n <= INT_MAX && n >= INT_MIN);
}

static bool	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static int	ps_atoi(char *nptr, bool *err)
{
	long long	res;
	int			i;
	int			sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && is_int(sign * res))
	{
		res = 10 * res + nptr[i] - '0';
		i++;
	}
	res *= sign;
	if (str[i])
		err = true;
	return (res);
}

bool	parse(int *res, char **nums, int size)
{
	int		i;
	bool	err;

	i = 0;
	err = false;
	while (i < size)
	{
		res[i] = ps_atoi(nums[i], &err);
		i++;
	}
	return (!err);
}

void	compress(int *res, int size)
{
	int	*dup;

	dup = (int *)malloc(size * sizeof(int));
	if (!dup)
		return ;
	ft_memcpy(dup, res, size * sizeof(int));
	qsort(dup, size, sizeof(int), cmp);
	for (int i = 0; i < size; i++)
		res[i] = (bsearch(res + i, dup, size, sizeof(int), cmp) - dup);
	free(dup);
}

int	*parse_and_compress(char **nums, int size)
{
	int	*res;

	res = (int *)malloc(size * sizeof(int));
	if (!res)
		return (NULL);
	if (!parse(res, nums, size))
		return (free(res), NULL);
	compress(res, size);
	if (!res)
		return (NULL);
	return (res);
}

int main(int argc, char **argv)
{
	t_stk	stk_a;
	t_stk	stk_b;

	memset(stk_a, 0, sizeof(t_stk));
	memset(stk_b, 0, sizeof(t_stk));
	parse(&stk_a, argv + 1, argc - 1);
}
