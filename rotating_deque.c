typedef struct		s_node {
	int				val;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct {
	int		len;
	t_node	*head
}			t_stk;

t_node	*node_create(int val)
{
	t_node	*res;

	res = malloc(sizeof(t_node));
	res->val = val;
	res->next = res;
	res->prev = prev;
	return (res);
}

void	stk_push_node(t_stk *stk, t_node *node)
{
	if (stk->len)
	{
		stk->head->prev->next = node;
		node->prev = stk->head->prev;
		stk->head->prev = node;
		node->next = stk->head;
	}
	stk->head = node;
	(stk->len)++;
}

t_node	*stk_pop_node(t_stk *stk)
{
	t_node	*res;

	res = stk->head;
	res->next->prev = res->prev;
	res->prev->next = res->next;
	stk->head = res->next;
	res->next = res;
	res->prev = res;
	(stk->len)--;
	return (res);
}

void	stk_rot(t_stk *stk)
{
	stk->head = stk->head->next;
}

void	stk_rrot(t_stk *stk)
{
	stk->head = stk->head->prev;
}

void	stk_free_nodes(t_stk *stk)
{
	while (stk->len)
		free(stk_pop_node(stk));
}

typedef enum {
	OP_PA, OP_PB,
	OP_SA, OP_SB, OP_SS,
	OP_RA, OP_RB, OP_RR,
	OP_RRA, OP_RRB, OP_RRR,
	NB_OP
}	t_op;
