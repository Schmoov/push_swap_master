#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void	print_perm(int *perm, int n)
{
	for (int i = 0; i < n - 1; i++)
		printf("%d ", perm[i]);
	printf("%d\n", perm[n-1]);
}

bool is_valid(int *perm, int curr)
{
	for (int i = 0; i < curr; i++)
		if (perm[i] == perm[curr])
			return false;
	return true;
}

void	backtrack(int *perm, int n, int curr)
{
	if (curr == n)
	{
		print_perm(perm, n);
		return ;
	}
	for (int i = 1; i <= n; i++)
	{
		perm[curr] = i;
		if (is_valid(perm, curr))
			backtrack(perm, n, curr + 1);
	}
}

int main(int argc, char**argv)
{
	int n = atoi(argv[1]);

	int *perm = malloc(n * sizeof(int));
	backtrack(perm, n, 0);
	free(perm);
}
