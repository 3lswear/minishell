/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:52:41 by talyx             #+#    #+#             */
/*   Updated: 2021/09/18 18:38:12 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_minishell *mini)
{
	t_command	*command;
	t_list		*commands;
	int			k;

	k = -1;
	commands = mini->commands;
	while (commands)
	{
		mini->fd.pid = 2;
		command = commands->content;
		if (is_redir(command))
			k = redirect(mini, command);
		if (command->pipe)
			mini->fd.pid = make_pipe(mini);
		if (mini->fd.pid == 1)
		{
			commands = commands->next;
			continue ;
		}
		if (k == 1)
			return (1);
		if (is_builtins(command))
			mini->exit_status = run_builtins(mini, command);
		else if (command->path)
			mini->exit_status = run_bins(mini, command);
		commands = commands->next;
		if (mini->fd.pid == 0)
			exit(mini->exit_status);
		close_fd(mini);
		reset_fd(mini);
	}
	return (0);
}
