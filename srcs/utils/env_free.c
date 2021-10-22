#include "minishell.h"

void	env_free(t_list **env)
{
	t_list	*tmp;
	t_list	*next;
	char	*line;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		line = tmp->content;
		free(line);
		free(tmp);
		tmp = next;
	}
	free(env);
}
