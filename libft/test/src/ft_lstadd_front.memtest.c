#include <criterion/criterion.h>
#include <stdlib.h>
#include "libft.h"

Test(lstadd_front, basics)
{
	int	a = 42;
	int	b = 0;
	int	c = -243;
	t_list	*list = NULL;
	t_list	*node_a = ft_lstnew((void *)&a);
	t_list	*node_b = ft_lstnew((void *)&b);
	t_list	*node_c = ft_lstnew((void *)&c);

	ft_lstadd_front(&list, node_a);
	cr_assert_eq(*(int *)list->content, a);
	cr_assert_eq(list->next, NULL);

	ft_lstadd_front(&list, node_b);
	cr_assert_eq(*(int *)list->content, b);
	cr_assert_eq(list->next, node_a);

	ft_lstadd_front(&list, node_c);
	cr_assert_eq(*(int *)list->content, c);
	cr_assert_eq(list->next, node_b);

	free(node_a);
	free(node_b);
	free(node_c);
}
