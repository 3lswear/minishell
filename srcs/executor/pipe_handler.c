#include "minishell.h"

t_pipe	*init_pipe(int pid, int fd[2])
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->pid = pid;
	pipe->pipe_fd[0] = fd[0];
	pipe->pipe_fd[1] = fd[1];
	return (pipe);
}

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
		if (flag == 1)
			i = re_input(mini, path);
		else
			i = run_heredoc(mini, path);
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

int	make_pipe(t_minishell *mini)
{
	t_pipe	pipes;

	pipe(pipes.pipe_fd);
	pipes.pid = fork();
	g_all_fd.fd_pipe_out = pipes.pipe_fd[1];
	g_all_fd.fd_pipe_in = pipes.pipe_fd[0];
	if (pipes.pid == 0)
	{
		if (pipes.pipe_fd[0] > 0)
			close(pipes.pipe_fd[0]);
		dup2(pipes.pipe_fd[1], 1);
		mini->fd.pid = 0;
		return (0);
	}
	else
	{
		if (pipes.pipe_fd[1] > 0)
			close(pipes.pipe_fd[1]);
		dup2(pipes.pipe_fd[0], 0);
		mini->fd.pid = pipes.pid;
		ft_lstadd_back(&mini->pipes,
			ft_lstnew(init_pipe(pipes.pid, pipes.pipe_fd)));
		return (1);
	}
}
