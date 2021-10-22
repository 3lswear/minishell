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
		g_all_fd.pid = 2;
		command = commands->content;
		if (is_redir(command))
			k = redirect(mini, command);
		if (command->pipe)
			g_all_fd.pid = make_pipe(mini);
		if (g_all_fd.pid == 1)
		{
			commands = commands->next;
			continue ;
		}
		if (k >= 512 || k == 1)
			return (1);
		if (is_builtins(command))
			mini->exit_status = run_builtins(mini, command);
		else if (command->path)
			mini->exit_status = run_bins(mini, command);
		commands = commands->next;
		if (g_all_fd.pid == 0)
			exit(mini->exit_status);
		close_fd();
		reset_fd();
	}
	return (0);
}
