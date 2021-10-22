#include "minishell.h"

int	is_redir(t_command *command)
{
	if (command->red || command->append)
	{
		return (1);
	}
	return (0);
}

int	run_redir(t_minishell *mini, t_redir *redir, int flag)
{
	t_list	*in;
	t_list	*out;
	char	*path;
	int		i;

	i = 0;
	in = redir->in;
	out = redir->out;
	while (in && i == 0)
	{
		path = in->content;
		if (flag == 1)
			i = re_input(mini, path);
		else
			i = run_heredoc(path);
		in = in->next;
	}
	while (out && i == 0)
	{
		path = out->content;
		i = re_output(mini, path, flag);
		out = out->next;
	}
	return (i);
}

int	redirect(t_minishell *mini, t_command *command)
{
	int	i;

	i = 0;
	if (command->red->in || command->red->out)
		i = run_redir(mini, command->red, 1);
	else if (command->append->in || command->append->out)
		i = run_redir(mini, command->append, 2);
	return (i);
}
