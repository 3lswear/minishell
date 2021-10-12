#ifndef LIST2_H

#include "minishell.h"
# define LIST2_H

typedef struct s_var
{
	char *name;
	char *value;
} t_var;

typedef struct s_list_head
{
	struct s_list_head *next;
} t_list_head;

typedef struct s_list_vars
{
	t_list_head list_head;
	t_var var;
} t_list_vars;

t_list_vars	*list_vars_new(char *name, char *value);
t_list_head	*list_last(t_list_head *list);
void		list_add_back(t_list_head **head, t_list_head *new);

#endif
