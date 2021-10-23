#include "minishell.h"

/* if-else-if-else statement to insert split in tokens, pass &li and &prev */
void	tokens_insert(t_list **split, t_list **li, t_list **prev,
		t_list **tokens)
{
	t_list *tmp;

	if (!split)
		(*prev) = (*li);
	else if (!(*prev))
	{
		tmp = ft_lstlast(*split);
		ft_lstadd_back(split, (*li)->next);
		word_li_free(*tokens);
		*tokens = *split;
		(*li) = tmp;
		(*prev) = (*li);
	}
	else
	{
		(*li) = ft_lstlast(*split);
		ft_lstadd_back(split, (*prev)->next->next);
		word_li_free((*prev)->next);
		(*prev)->next = *split;
		(*prev) = (*li);
	}
}

/* same as tokens_insert, but make li first in split */
void	tokens_insert2(t_list **split, t_list **li, t_list **prev,
		t_list **tokens)
{
	if (!split)
		(*prev) = (*li);
	else if (!(*prev))
	{
		ft_lstadd_back(split, (*li)->next);
		word_li_free(*tokens);
		*tokens = *split;
		(*li) = (*split);
		(*prev) = (*li);
	}
	else
	{
		(*li) = (*split);
		ft_lstadd_back(split, (*prev)->next->next);
		word_li_free((*prev)->next);
		(*prev)->next = *split;
		(*prev) = (*li);
	}
}
