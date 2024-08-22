#include "push_swap.c"

int solved(deque *a, deque *b)
{
	if (b->size)
		return 0;
	node	*tmp = a->head;
	for (int i = 0; i < a->size - 1; i++)
	{
		if (tmp->val > tmp->next->val)
			return 0;
		tmp = tmp->next;
	}
	return 1;
}

int main(int c, char **v)
{
	char	*op_list[] = {"sa","sb","ss","pa","pb","ra","rb","rr","rra","rrb","rrr"};
	char	*op_rev[] =  {"sa","sb","ss","pb","pa","rra","rrb","rrr","ra","rb","rr"};
	deque *a=create_deque();	
	deque *b=create_deque();	
	for (int i = 1; i <= c; i++)
		rpush_deque(a,atoi(v[i]));
	int nb_op = 0;

	while (1)
	{
		for (int i = 0; i < nb_op; i++)
			for (int j = 0
