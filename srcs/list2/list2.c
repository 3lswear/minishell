#include "minishell.h"

t_list_head *list_last(t_list_head *list)
{
	if (!list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	list_add_back(t_list_head **head, t_list_head *new)
{
	t_list_head	*p;

	if (!head || !new)
		return ;
	if (*head)
	{
		p = list_last(*head);
		p->next = new;
	}
	else
		*head = new;
}
