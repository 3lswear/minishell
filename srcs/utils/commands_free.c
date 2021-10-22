#include "minishell.h"

static void	cmd_free(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			free(cmd->arg[i]);
			i++;
		}
		free(cmd->arg);
	}
	if (cmd->red)
	{
		string_list_free(&cmd->red->in);
		string_list_free(&cmd->red->out);
		free(cmd->red);
	}
	if (cmd->append)
	{
		string_list_free(&cmd->append->in);
		string_list_free(&cmd->append->out);
		free(cmd->append);
	}
	free (cmd);
}

void	commands_free(t_list *commands)
{
	t_list	*tmp;

	while (commands)
	{
		tmp = commands->next;
		cmd_free(commands->content);
		free(commands);
		commands = tmp;
	}
	free(commands);
}
