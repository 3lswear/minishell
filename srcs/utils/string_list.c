#include "minishell.h"

void	string_list_free(t_list **list)
{
	t_list *li;
	t_list *tmp;

	li = *list;
	tmp = NULL;
	while (li)
	{
		tmp = li->next;
		free(li->content);
		free(li);
		li = NULL;
		if (tmp)
			li = tmp;
		else
			break;
	}
}
