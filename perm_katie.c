#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fac(int n){return (n<2?1:n*fac(n-1));}
int perm_to_rank(int *perm, int n);

void	rot_array(int *arr, int len)
{
	int 	tmp = arr[len - 1];
	for (int i = len - 1; i > 0; i--)
		arr[i] = arr[i - 1];
	arr[0] = tmp;
}
	
void print_arr(int *arr, int n)
{
	printf("%d: ", perm_to_rank(arr,n));
	printf("[%d",*arr);
	for (int i = 1; i <n; i++)
		printf(",%d",arr[i]);
	printf("]\n");
}
	//BACKTRACKING
int is_valid(int *arr, int n)
{
	for (int i = 0; i<n; i++)
		if (arr[i] == arr[n])
			return 0;
	return 1;
}

void print_perm_backtracking(int *arr, int n, int step)
{
	if (step == n)
	{
		print_arr(arr, n);
		return ;
	}
	for (int i = 1; i <= n; i++)
	{
		arr[step] = i;
		if (is_valid(arr, step))
			print_perm_backtracking(arr,n,step+1);
	}
}

	//LEXICOGRAPHIC ORDER
int perm_to_rank(int *perm, int n)
{
	int res = 0;
	for (int i = 0; i<n-1; i++)
	{
		for (int j = i+1; j<n; j++)
			if (perm[j]<perm[i])
				res++;
		res *=(n-1-i);
	}
	return (res);
}

void	rank_to_perm(int *perm, int n, int rank)
{
	for (int i = 0; i < n; i++)
		perm[i] = i + 1;
	for (int i = 0; i < n - 1; i++)
	{
		rot_array(perm + i, 1 + (rank  / fac(n-i-1)));
		rank %= fac(n-1-i);
	}
}

void	print_perm_ranking(int *perm, int n)
{
	for (int rank = 0; rank < fac(n); rank++)
	{
		rank_to_perm(perm, n, rank);
		print_arr(perm, n);
	}
}

int main(int c, char **v)
{
	int n = atoi(v[1]);
	int *arr = malloc(n*sizeof(int));

//	print_perm_ranking(arr, n);
	print_perm_backtracking(arr, n, 0);
	free(arr);
}
