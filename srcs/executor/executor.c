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

int	run_command(t_minishell *mini, t_command *command, int *pipe_count)
{
	int	k;

	k = -1;
	if (is_redir(command))
		k = redirect(mini, command);
	if (k >= 512 || k == 1)
		return (1);
	if (command->pipe)
	{
		(*pipe_count)++;
		mini->fd.error = make_pipe(mini);
	}
	if (mini->fd.error == 1)
		return (0);
	if (is_builtins(command))
			mini->exit_status = run_builtins(mini, command);
	else if (command->path)
		mini->exit_status = run_bins(mini, command);
	if (mini->fd.error == 0)
	{
		close_and_reset_all();
		exit(mini->exit_status);
	}
	return (0);
}
//cat /dev/random | head -c 100 | wc -c
int	execute(t_minishell *mini)
{
	t_command	*command;
	t_list		*commands;
	int			check;
	int			pipe_count;

	pipe_count = 0;
	commands = mini->commands;
	check = 0;
	while (commands)
	{
		mini->fd.error = 2;
		command = commands->content;
		check = run_command(mini, command, &pipe_count);
		if (check == 1)
			return (1);
		commands = commands->next;
		if (mini->fd.error != 1)
			close_and_reset_all();
	}
	while (pipe_count > 0)
	{
		waitpid(-1, &mini->exit_status, 0);
		pipe_count--;
	}
	return (0);
}
