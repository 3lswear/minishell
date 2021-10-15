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

	while (mini->commands)
	{
		mini->fd.pid = 2;
		command = mini->commands->content;
		if (is_redir(command))
			redirect(mini, command);
		if (command->pipe)
			mini->fd.pid = make_pipe(mini);
		if (mini->fd.pid == 1)
		{
			mini->commands = mini->commands->next;
			continue ;
		}
		if (is_builtins(command))
			run_builtins(mini, command);
		else
			run_bins(mini, command);
		mini->commands = mini->commands->next;
		if (mini->fd.pid == 0)
			exit(mini->exit_status);
		close_fd(mini);
		reset_fd(mini);
	}
	return (1);
}