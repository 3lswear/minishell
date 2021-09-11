#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

# define PIPE 	0
# define REDIR	1

// ╰─ sudo apt-get install libreadline8 libreadline-dev  установить readline.

typedef struct s_env
{
	struct s_env	*next;
	char			*value;
}				t_env;

typedef struct s_redir
{
	char	*in;
	char	*out;
}				t_redir;

typedef struct s_command
{
	char	*path;
	char	**arg;
	char	**envp;
	int		pipe;
	t_redir	*red;
	t_redir	*append;
}				t_command;

typedef struct s_minishell
{
	int		fd_in;
	int		fd_out;
	t_list	*commands;
	t_env	*env;
	
}				t_minishell;

void	read_line(t_minishell *mini);
void	parse_env(t_minishell *mini, char **env);
void	parse_comand(t_minishell *mini, char *line);
void	sig_handler(int sig);


#endif