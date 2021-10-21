#include "minishell.h"

int	update_env(t_list **env, char *key, char *new_line)
{
	t_list	*tmp;
	t_list	*temp;
	t_list	*new;
	char	*line;

	tmp = *env;
	temp = *env;
	while (tmp)
	{
		line = (char *)tmp->content;
		if (!ft_strncmp(line, key, ft_strlen(key)))
		{
			new = ft_lstnew(ft_strdup(new_line));
			temp->next = new;
			new->next = tmp->next;
			free(tmp->content);
			free(tmp);
			return (1);
		}
		temp = tmp;
		tmp = tmp->next;
	}
	return (0);
}
