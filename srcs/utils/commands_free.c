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
