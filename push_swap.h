#include "libft/libft.h"

		//DATA_STRUCTURE
typedef struct		s_node {
	int				val;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct {
	int		len;
	t_node	*head;
}			t_stk;

t_node	*node_create(int val);
void	stk_push_node(t_stk *stk, t_node *node);
t_node	*stk_pop_node(t_stk *stk);
void	stk_rot(t_stk *stk);
void	stk_rrot(t_stk *stk);
void	stk_free_nodes(t_stk *stk);

typedef enum {
	OP_PA, OP_PB,
	OP_SA, OP_SB, OP_SS,
	OP_RA, OP_RB, OP_RR,
	OP_RRA, OP_RRB, OP_RRR,
	NB_OP
}	t_op;


bool	ps_parse(int *res, char **nums, int size);
bool	compress(int *res, int size);
int	*parse_and_compress(char **nums, int size);
int main(int argc, char **argv);
