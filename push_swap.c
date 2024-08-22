#include "ddeck.c"
#include "perm.c"
#include <stdio.h>
#include <string.h>

void deque_swap(deque *d)
{
	if (d->size < 2)
		return;
	int tmp = d->head->val;
	d->head->val = d->head->next->val;
	d->head->next->val = tmp;
}

void deque_push(deque *from, deque *to)
{
	rpush_deque(to, rpop_deque(from));
}

void deque_rot(deque *d)
{
	d->head = d->head->next;
}

void deque_rrot(deque *d)
{
	d->head = d->head->prev;
}

void process_token(char *token, deque *a, deque *b)
{
	if (!strcmp(token,"sa")) {
		deque_swap(a);
	} else if (!strcmp(token,"sb")) {
		deque_swap(b);
	} else if (!strcmp(token,"ss")) {
		deque_swap(a);
		deque_swap(b);
	} else if (!strcmp(token,"pa")) {
		deque_push(b,a);
	} else if (!strcmp(token,"pb")) {
		deque_push(a,b);
	} else if (!strcmp(token,"ra")) {
		deque_rot(a);
	} else if (!strcmp(token,"rb")) {
		deque_rot(b);
	} else if (!strcmp(token,"rr")) {
		deque_rot(a);
		deque_rot(b);
	} else if (!strcmp(token,"rra")) {
		deque_rrot(a);
	} else if (!strcmp(token,"rrb")) {
		deque_rrot(b);
	} else if (!strcmp(token,"rrr")) {
		deque_rrot(a);
		deque_rrot(b);
	}
}

void print_deque(deque *d)
{
	node	*tmp = d->head;

	for (int i = 0; i<(d->size); i++)
	{
		if (i)
			printf(" ");
		printf("%d",tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_state (deque *a, deque *b)
{
	print_deque(a);
	print_deque(b);
	puts("----------------------");
}

void exex(char *ops, deque *a, deque *b)
{

	print_state(a,b);

	char *token = strtok(ops, " ");
	while (token)
	{
		process_token(token, a, b);
		print_state(a,b);
		token = strtok(NULL, " ");
	}
}
/*
int main()
{
	deque *a =create_deque();
	deque *b =create_deque();

	rpush_deque(a,8);
	rpush_deque(a,5);
	rpush_deque(a,6);
	rpush_deque(a,3);
	rpush_deque(a,1);
	rpush_deque(a,2);
	exec(strdup("sa pb pb pb ra rb rra rrb sa pa pa pa"),a , b);
}
*/
