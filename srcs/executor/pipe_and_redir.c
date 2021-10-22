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
			return (1);
	}
	return (0);
}

int	run_redir(t_minishell *mini, t_redir *redir, int flag)
{
	t_list	*in;
	t_list	*out;
	char	*path;
	int		i;

	i = 0;
	in = redir->in;
	out = redir->out;
	while (in && i == 0)
	{
		path = in->content;
		i = re_input(mini, path);
		in = in->next;
	}
	while (out && i == 0)
	{
		path = out->content;
		i = re_output(mini, path, flag);
		out = out->next;
	}
	return (i);
}

int	redirect(t_minishell *mini, t_command *command)
{
	int	i;

	i = 0;
	if (command->red->in || command->red->out)
		i = run_redir(mini, command->red, 1);
	else if (command->append->in || command->append->out)
		i = run_redir(mini, command->append, 2);
	return (i);
}

int	re_input(t_minishell *mini, char *path)
{
	if (mini->fd.redir_in > 0)
		close(mini->fd.redir_in);
	mini->fd.redir_in = open(path, O_RDONLY);
	if (mini->fd.redir_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(mini->fd.redir_in, 0);
	return (0);
}

int	re_output(t_minishell *mini, char *path, int type)
{
	int	fd;

	if (mini->fd.redir_out > 0)
		close(mini->fd.redir_out);
	if (type == 1)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	mini->fd.redir_out = fd;
	if (mini->fd.redir_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(mini->fd.redir_out, 1);
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
