#include <stdlib.h>
#include <stdio.h>
int print_uint128(__uint128_t n) {
  if (n == 0)  return printf("0\n");

  char str[40] = {0}; // log10(1 << 128) + '\0'
  char *s = str + sizeof(str) - 1; // start at the end
  while (n != 0) {
    if (s == str) return -1; // never happens

    *--s = "0123456789"[n % 10]; // save last digit
    n /= 10;                     // drop it
  }
  return printf("%s\n", s);
}
int main()
{
	__uint128_t *arr = calloc(100, 8);
	arr[1] = 2;
	arr[2] = 1;
	arr[3] = 3;
	for (int n = 4; n < 101; n++)
	{
		for (int i = 1; i <= (n+1)/4; i++)
			arr[n] += arr[2*i-1]*arr[n-2*i+1];
		print_uint128(arr[n]);
	}

}
