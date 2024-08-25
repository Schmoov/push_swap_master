#include "push_swap.h"

static int	cmp(int *a, int *b)
{
	if (*a > *b)
		return (1);
	if (*a < *b)
		return (-1);
	return (0);
}

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
	if (nptr[i] || !is_int(res))
		*err = true;
	return (res);
}

bool	ps_parse(int *res, char **nums, int size)
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

bool	compress(int *res, int size)
{
	int	*dup;

	dup = (int *)malloc(size * sizeof(int));
	if (!dup)
		return (false);
	ft_memcpy(dup, res, size * sizeof(int));
	qsort(dup, size, sizeof(int), cmp);
	for (int i = 0; i < size - 1; i++)
		if (dup[i] == dup[i + 1])
			return (free(dup), false);
	for (int i = 0; i < size; i++)
		res[i] = ((int *)bsearch(res + i, dup, size, sizeof(int), cmp) - dup);
	free(dup);
	return (true);
}

int	*parse_and_compress(char **nums, int size)
{
	int	*res;

	res = (int *)malloc(size * sizeof(int));
	if (!res)
		return (NULL);
	if (!ps_parse(res, nums, size))
		return (free(res), NULL);
	if (!compress(res, size))
		return (free(res), NULL);
	return (res);
}
