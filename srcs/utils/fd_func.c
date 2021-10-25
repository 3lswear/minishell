/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:57:18 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/25 15:57:19 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(void)
{
	g_all_fd.redir_in = -1;
	g_all_fd.redir_out = -1;
	g_all_fd.fd_pipe_in = -1;
	g_all_fd.fd_pipe_out = -1;
	g_all_fd.pid = 2;
	g_all_fd.end_herecode = 1;
	g_all_fd.not_line = 0;
	g_all_fd.heredoc_on = 0;
}

void	reset_fd(void)
{
	dup2(g_all_fd.fd_in, 0);
	dup2(g_all_fd.fd_out, 1);
}

void	close_fd(void)
{
	if (g_all_fd.redir_in > 0)
		close(g_all_fd.redir_in);
	if (g_all_fd.redir_out > 0)
		close(g_all_fd.redir_out);
	if (g_all_fd.fd_pipe_in > 0)
		close(g_all_fd.fd_pipe_in);
	if (g_all_fd.fd_pipe_out > 0)
		close(g_all_fd.fd_pipe_out);
}

void	close_and_reset_all(void)
{
	if (g_all_fd.redir_in > 0)
		close(g_all_fd.redir_in);
	if (g_all_fd.redir_out > 0)
		close(g_all_fd.redir_out);
	if (g_all_fd.fd_pipe_in > 0)
		close(g_all_fd.fd_pipe_in);
	if (g_all_fd.fd_pipe_out > 0)
		close(g_all_fd.fd_pipe_out);
	dup2(g_all_fd.fd_in, 0);
	dup2(g_all_fd.fd_out, 1);
}

void	close_and_reset_out(void)
{
	if (g_all_fd.fd_pipe_out)
		close(g_all_fd.fd_pipe_out);
	dup2(g_all_fd.fd_out, 1);
}
