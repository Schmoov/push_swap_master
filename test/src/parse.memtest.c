#include <criterion/criterion.h>
#include "push_swap.h"

Test(parse_and_compress, easiest)
{
	char **nums = malloc(12 * sizeof(char *));
	nums[0] = "0";
	nums[1] = "1";
	nums[2] = "2";
	nums[3] = "3";
	nums[4] = "4";
	nums[5] = "5";
	nums[6] = "6";
	nums[7] = "7";
	nums[8] = "8";
	nums[9] = "9";
	nums[10] = "10";
	nums[11] = "11";

	int expected[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	int *res = parse_and_compress(nums, 12);
	cr_expect_arr_eq(res, expected, 12*sizeof(int));
	free(nums);
	free(res);
}

Test(parse_and_compress, easy)
{
	char **nums = malloc(6 * sizeof(char *));
	nums[0] = "0";
	nums[1] = "1";
	nums[2] = "5";
	nums[3] = "3";
	nums[4] = "4";
	nums[5] = "2";

	int expected[6] = {0, 1, 5, 3, 4, 2};

	int *res = parse_and_compress(nums, 6);
	cr_expect_arr_eq(res, expected, 6*sizeof(int));
	free(nums);
	free(res);
}

Test(parse_and_compress, compress)
{
	char **nums = malloc(6 * sizeof(char *));
	nums[0] = "-7";
	nums[1] = "1";
	nums[2] = "1435";
	nums[3] = "-3004";
	nums[4] = "4";
	nums[5] = "12";

	int expected[6] = {1, 2, 5, 0, 3, 4};

	int *res = parse_and_compress(nums, 6);
	cr_expect_arr_eq(res, expected, 6*sizeof(int));
	free(nums);
	free(res);
}

Test(parse_and_compress, invalid_strings)
{
	char **nums = malloc(2 * sizeof(char *));
	nums[0] = "-7";
	nums[1] = "1-1";
	int expected[2] = {0, 1};

	int *res = parse_and_compress(nums, 2);
	cr_expect_null(res);

	nums[1] = "2147483647";
	res = parse_and_compress(nums, 2);
	cr_expect_arr_eq(res, expected, 2*sizeof(int));
	free(res);
	
	nums[0] = "-2147483648";
	res = parse_and_compress(nums, 2);
	cr_expect_arr_eq(res, expected, 2*sizeof(int));
	free(res);

	nums[1] = "2147483648";
	res = parse_and_compress(nums, 2);
	cr_expect_null(res);

	nums[1] = "21";
	nums[0] = "-2147483649";
	res = parse_and_compress(nums, 2);
	cr_expect_null(res);

	free(nums);
}
