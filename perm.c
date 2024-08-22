#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fac(int n)
{
	return (n == 1 ? 1 : n*fac(n-1));
}

int rank_perm(int *perm, int n)
{
	if (n==1)
		return 0;
	int res = 0;
	int idx = 0;
	for (int i = 0; i<n; i++)
		if (perm[i]<perm[0])
			idx++;
	res += fac(n-1)*idx;
	res += rank_perm(perm+1,n-1);
	return (res);
}
void print_arr(int *arr, int n)
{
	printf("%d: ",rank_perm(arr,n));
	printf("[%d",*arr);
	for (int i = 1; i <n; i++)
		printf(",%d",arr[i]);
	printf("]\n");
}

int is_valid(int *arr, int n)
{
	for (int i = 0; i<n && arr[i] ; i++)
		for (int j = i+1; j < n && arr[j]; j++)
			if (arr[i] == arr[j])
				return 0;
	return 1;
}

void print_perm(int *arr, int n, int step)
{
	if (step == n)
		print_arr(arr, n);
	else
	{
		for (int i = 1; i <= n; i++)
		{
			arr[step] = i;
			if (is_valid(arr,n))
				print_perm(arr,n,step+1);
		}
		arr[step] = 0;
	}
}

/*
int main(int c, char **v)
{
	int n = atoi(v[1]);
	int arr[n];
	bzero(arr,sizeof(int)*n);
	print_perm(arr,n,0);
}
*/
