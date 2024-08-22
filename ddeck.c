#include <stdlib.h>

typedef struct		node {
	int		val;
	struct node	*next;
	struct node	*prev;
}			node;

typedef struct deque { 
	int	size;
	node	*head;
}		deque;

node	*create_node(int n)
{
	node	*new = malloc(sizeof(node));
	new->val = n;
	return new;
}

deque	*create_deque()
{
	deque	*new = malloc(sizeof(deque));
	new->size = 0;
	return (new);
}

void	rpush_deque (deque *d, int val)
{
	node *new = create_node(val);
	if (d->size == 0)
	{
		d->size = 1;
		new->next = new;	
		new->prev = new;
		d->head = new;
		return;
	}	
	new->next = d->head;
	new->prev = d->head->prev;
	d->head->prev->next = new;
	d->head->prev = new;
	(d->size)++;
	d->head = new;
}

void	lpush_deque (deque *d, int val)
{
	node *new = create_node(val);
	if (d->size == 0)
	{
		d->size = 1;
		new->next = new;	
		new->prev = new;
		d->head = new;
		return;
	}	
	new->next = d->head;
	new->prev = d->head->prev;
	d->head->prev->next = new;
	d->head->prev = new;
	(d->size)++;
}

int	rpop_deque(deque *d)
{
	node	*todel = d->head;
	int res = todel->val;

	todel->prev->next = todel->next;
	todel->next->prev = todel->prev;
	d->head = todel->next;
	(d->size)--;
	
	free(todel);
	return (res);
}

int	lpop_deque(deque *d)
{
	node	*todel = d->head->prev;
	int res = todel->val;

	todel->prev->next = todel->next;
	todel->next->prev = todel->prev;
	(d->size)--;
	
	free(todel);
	return (res);
}

