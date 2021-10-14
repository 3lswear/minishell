/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:02:07 by talyx             #+#    #+#             */
/*   Updated: 2021/09/18 19:01:25 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int re_input(t_minishell *mini, t_redir *input)
// {
// 	if (mini->fd_in > 0)
// 		close(mini->fd_in);
// 	mini->fd_in = open(input->in, O_RDONLY);
// 	if (mini->fd_in == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(input->in, 2);
// 		ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		mini->exit_status = 1;
// 		return (0);
// 	}
// 	dup2(mini->fd_in, mini->STDin);
// 	return (1);
// }

// int	redirect(t_minishell *mini, t_redir *redir, int type)
// {
// 	if (mini->fd_out > 0)
// 		close(mini->fd_out);
// 	if (type == 1)
// 		mini->fd_out = open(redir->out, O_CREAT | O_WRONLY | O_TRUNC);
// 	else
// 		mini->fd_out = open(redir->out, O_CREAT | O_WRONLY | O_APPEND);
// 	if (mini->fd_out == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(redir->out, 2);
// 		ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		mini->exit_status = 1;
// 		return (0);
// 	}
// 	dup2(mini->fd_out, mini->STDout);
// 	return (1);
// }

int	make_pipe(t_minishell *mini)
{
	pid_t	pid;
	int		fd_pipe[2];

	pipe(fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		if (fd_pipe[0] > 0)	
			close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		mini->fd.fd_pipe_in = fd_pipe[0];
		return (0);
	}
	else
	{
		if (fd_pipe[1] > 0)
			close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		waitpid(pid, &mini->exit_status, 0);
		mini->fd.fd_pipe_out = fd_pipe[0];
		return (1);
	}
}