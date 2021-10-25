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

void	run_heredoc_chile(t_minishell *mini, char *eof)
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
			return ;
		}
		dup2(g_all_fd.fd_pipe_out, 1);
		if (!ft_strequ(eof, line))
		{
			mini->sub_line = heredoc_subst(line, mini);
			ft_putendl_fd(mini->sub_line, 1);
			free (mini->sub_line);
		}
	}
	free(line);
	close_and_reset_out();
}

int	run_heredoc(t_minishell *mini, char *eof)
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
		run_heredoc_chile(mini, eof);
		exit(0);
	}
	else
	{
		close(fd_pipe[1]);
		g_all_fd.heredoc_on = 1;
		waitpid(pid, &i, 0);
		g_all_fd.heredoc_on = 0;
		if (i <= 256)
			dup2(fd_pipe[0], 0);
		return (i);
	}
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
