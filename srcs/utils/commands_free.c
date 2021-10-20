#include "minishell.h"

static void	cmd_free(t_command *cmd)
{
	int i;

	i = 0;
	/* if (cmd->path) */
	/* 	free(cmd->path); */
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
		free(cmd->red->in);
		free(cmd->red->out);
		free(cmd->red);
	}
	if (cmd->append)
	{
		free(cmd->append->in);
		free(cmd->append->out);
		free(cmd->append);
	}

	//TODO: free redirects
	//
	free (cmd);

}

void	commands_free(t_list *commands)
{
	t_list *tmp;

	while (commands)
	{
		tmp = commands->next;
		cmd_free(commands->content);
		free(commands);
		commands = tmp;
	}
	free(commands);
}
