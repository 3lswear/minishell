#include "minishell.h"

int	print_export(t_list **env)
{
	char	*line;
	t_list	*tmp;

	tmp = *env;
	tmp = tmp->next;
	while (tmp)
	{
		line = tmp->content;
		ft_putstr("declare -x ");
		ft_putstr(line);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	return (1);
}

int	ft_error_export(char *arg, int error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	if (error == 0)
		ft_putstr_fd("\': not valid in this contex ", 2);
	else if (error == -1)
		ft_putstr_fd("\': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
