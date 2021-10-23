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

int	run_heredoc_chile(char *eof)
{
	char	*line;

	line = ft_strdup("");
	while (!ft_strequ(eof, line))
	{
		dup2(g_all_fd.fd_out, 1);
		free(line);
		line = readline("herecode> ");
		if (!line)
		{
			free(line);
			close_and_reset_all();
			ft_putstr("\n");
			return (0);
		}
		dup2(g_all_fd.fd_pipe_out, 1);
		if (!ft_strequ(eof, line))
			ft_putendl_fd(line, 1);
	}
	free(line);
	close_and_reset_out();
	return (0);
}

int	run_heredoc(char *eof)
{
	int		fd_pipe[2];
	pid_t	pid;
	int		i;

	close_and_reset_all();
	pipe(fd_pipe);
	pid = fork();
	g_all_fd.fd_pipe_out = fd_pipe[1];
	g_all_fd.fd_pipe_in = fd_pipe[0];
	if (pid == 0)
	{
		g_all_fd.end_herecode = 0;
		i = run_heredoc_chile(eof);
		exit(0);
	}
	else
	{
		if (fd_pipe[1] > 0)
			close(fd_pipe[1]);
		waitpid(pid, &i, 0);
		if (i <= 256)
			dup2(fd_pipe[0], 0);
		return (i);
	}
	return (0);
}

int	re_input(t_minishell *mini, char *path)
{
	if (g_all_fd.redir_in > 0)
		close(g_all_fd.redir_in);
	g_all_fd.redir_in = open(path, O_RDONLY);
	if (g_all_fd.redir_in == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(g_all_fd.redir_in, 0);
	return (0);
}

int	re_output(t_minishell *mini, char *path, int type)
{
	int	fd;

	if (g_all_fd.redir_out > 0)
		close(g_all_fd.redir_out);
	if (type == 1)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	g_all_fd.redir_out = fd;
	if (g_all_fd.redir_out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	dup2(g_all_fd.redir_out, 1);
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
		mini->fd.pid = 0;
		g_all_fd.fd_pipe_in = fd_pipe[0];
		return (0);
	}
	else
	{
		if (fd_pipe[1] > 0)
			close(fd_pipe[1]);
		dup2(fd_pipe[0], 0);
		waitpid(pid, &mini->exit_status, 0);
		g_all_fd.fd_pipe_out = fd_pipe[1];
		mini->fd.pid = pid;
		return (1);
		mini->fd.not_line = 0;
	}
}
