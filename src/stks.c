#include "../push_swap.h"

void	stks_init(int *input, int input_len, t_stk *stk_a, t_stk *stk_b)
{
	int		i;
	t_node	*tmp;

	stk_a->len = 0;
	stk_b->len = 0;
	stk_b->head = NULL;
	i = input_len - 1;
	while (i > -1)
	{
		tmp = node_create(input[i]);
		if (!tmp)
		{
			stk_free_nodes(stk_a);
			stk_a->len = 0;
			return ;
		}
		stk_push_node(stk_a, tmp);
		i--;
	}
}

void	stks_destroy(t_stk *stk_a, t_stk *stk_b)
{
	stk_free_nodes(stk_a);
	stk_free_nodes(stk_b);
}

bool	stks_is_solved(t_stk *stk_a, t_stk *stk_b)
{
	t_node	*tmp;

	if (stk_b->len)
		return (false);
	if (!stk_a->head || stk_a->head->val)
		return (false);
	tmp = stk_a->head;
	while (tmp->next->val)
	{
		if (tmp->val > tmp->next->val)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

void	stks_execute(t_op *moves, int moves_len, t_stk *stk_a, t_stk *stk_b)
{
	int	i;

	i = 0;
	while (i < moves_len)
	{
		ps_op_to_func(moves[i])(stk_a, stk_b);
		i++;
	}
}

void	stks_print(t_stk *a, t_stk *b)
{
	t_node	*tmp = a->head;
	for (int i = 0; i < a->len; i++)
	{
		ft_printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("|");
	tmp = b->head;
	for (int i = 0; i < b->len; i++)
	{
		ft_printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
