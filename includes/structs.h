/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:59:06 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 17:59:07 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_env
{
	struct s_env	*next;
	char			*value;
}				t_env;

typedef struct s_redir
{
	t_list	*in;
	t_list	*out;
}				t_redir;

typedef struct s_command
{
	char	*path;
	char	**arg;
	int		pipe;
	t_redir	*red;
	t_redir	*append;
}				t_command;

typedef struct s_fd
{
	int	pid;
	int	fd_in;
	int	fd_out;
	int	redir_in;
	int	redir_out;
	int	fd_pipe_in;
	int	fd_pipe_out;
	int	end_herecode;
	int	not_line;
	int	error;
}			t_fd;

typedef struct s_minishell
{
	t_fd	fd;
	int		exit;
	int		exit_status;
	int		parse_status;
	char	*line;
	char	**arg;
	char	**envp;
	t_list	*commands;
	t_list	**env;
	char	*prompt;
}				t_minishell;
#endif
