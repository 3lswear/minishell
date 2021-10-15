#include "minishell.h"

t_fd	init_fd()
{
	t_fd	fd;

	fd.fd_in = dup(0);
	fd.fd_out = dup(1);
	fd.fd_pipe_in = -1;
	fd.fd_pipe_out = -1;
	fd.pid = 2;
	return (fd);
}

void	reset_fd(t_minishell *mini)
{
	dup2(mini->fd.fd_in , 0);
	dup2(mini->fd.fd_out , 1);
}

void	close_fd(t_minishell *mini)
{
	close(mini->fd.fd_redir_in);
	close(mini->fd.fd_redir_out);
	close(mini->fd.fd_pipe_in);
	close(mini->fd.fd_pipe_out);
}