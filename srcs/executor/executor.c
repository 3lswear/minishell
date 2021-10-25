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

void	wait_and_clear(t_minishell *mini)
{
	int		pipe_status;
	int		status;
	t_pipe	*pipes;
	t_list	*tmp;
	t_list	*tmp_next;

	tmp = mini->pipes;
	while (tmp)
	{
		pipes = tmp->content;
		tmp_next = tmp->next;
		close(pipes->pipe_fd[0]);
		close(pipes->pipe_fd[1]);
		free(tmp);
		free(pipes);
		tmp = tmp_next;
	}
	pipe_status = 0;
	while (pipe_status != -1)
	{
		pipe_status = wait(&status);
	}
}

int	run_command(t_minishell *mini, t_command *command)
{
	int	k;

	k = -1;
	if (is_redir(command))
		k = redirect(mini, command);
	if (k >= 512 || k == 1)
		return (1);
	if (command->pipe)
		mini->fd.error = make_pipe(mini);
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

int	execute(t_minishell *mini)
{
	t_command	*command;
	t_list		*commands;
	int			check;

	commands = mini->commands;
	check = 0;
	while (commands)
	{
		mini->fd.error = 2;
		command = commands->content;
		check = run_command(mini, command);
		if (check == 1)
			return (1);
		commands = commands->next;
		if (mini->fd.error != 1)
			close_and_reset_all();
	}
	wait_and_clear(mini);
	return (0);
}
