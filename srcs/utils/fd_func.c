#include "minishell.h"

void	init_fd(void)
{
	g_all_fd.fd_in = dup(0);
	g_all_fd.fd_out = dup(1);
	g_all_fd.redir_in = -1;
	g_all_fd.redir_out = -1;
	g_all_fd.fd_pipe_in = -1;
	g_all_fd.fd_pipe_out = -1;
	g_all_fd.pid = 2;
	g_all_fd.end_herecode = 1;
	g_all_fd.not_line = 0;
}

void	reset_fd(void)
{
	dup2(g_all_fd.fd_in, 0);
	dup2(g_all_fd.fd_out, 1);
}

void	close_fd(void)
{
	close(g_all_fd.redir_in);
	close(g_all_fd.redir_out);
	close(g_all_fd.fd_pipe_in);
	close(g_all_fd.fd_pipe_out);
}

void	close_and_reset_all(void)
{
	close(g_all_fd.redir_in);
	close(g_all_fd.redir_out);
	close(g_all_fd.fd_pipe_in);
	close(g_all_fd.fd_pipe_out);
	dup2(g_all_fd.fd_in, 0);
	dup2(g_all_fd.fd_out, 1);
}

void	close_and_reset_out(void)
{
	close(g_all_fd.fd_pipe_out);
	dup2(g_all_fd.fd_out, 1);
}
