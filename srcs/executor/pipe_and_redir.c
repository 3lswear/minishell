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

int	is_redir(t_command *command)
{
	if (command->red || command->append)
	{
		if (command->red->in || command->red->out
			|| command->append->in || command->append->out)
			return (1);
	}
	return(0);
}

int	redirect(t_minishell *mini, t_command *command)
{
	int i;

	i = 0;
	if (command->red->in)
		i = re_input(mini, command->red);
	if (command->append->in && i == 0)
		i = re_input(mini, command->append);
	if (command->red->out && i == 0)
		i = re_output(mini, command->red, 1);
	if (command->append->out && i == 0)
		i = re_output(mini, command->append, 2);
	return (i);
}

int re_input(t_minishell *mini, t_redir *input)
{
	if (mini->fd.fd_redir_in > 0)
		close(mini->fd.fd_redir_in);
	mini->fd.fd_redir_in = open(input->in, O_RDONLY);
	if (mini->fd.fd_redir_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input->in, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(mini->fd.fd_redir_in, 0);
	return (0);
}

int	re_output(t_minishell *mini, t_redir *redir, int type)
{
	if (mini->fd.fd_redir_out > 0)
		close(mini->fd.fd_redir_out);
	if (type == 1)
		mini->fd.fd_redir_out = open(redir->out, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		mini->fd.fd_redir_out = open(redir->out, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (mini->fd.fd_redir_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir->out, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(mini->fd.fd_redir_out, 1);
	return (0);
}

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

void	open_input()
{
	char	*str;
	int		i;

	str = NULL;
	while ((i = get_next_line(0, &str)))
	{
		ft_putendl_fd(str, 1);
	}
}