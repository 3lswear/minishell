#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include "libft.h"

# define PIPE 	0
# define REDIR	1

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
	char	*option;
	int		pipe;
	t_redir	*red;
	t_redir	*append;
}				t_command;

typedef struct s_minishell
{
	int		fd_in;
	int		fd_out;
	int		exit;
	int		exit_status;
	char	*line;
	t_list	*commands;
	t_list	*env;
}				t_minishell;

int		ft_strlen2(char **str);
int		read_line(t_minishell *mini);
void	parse_env(t_minishell *mini, char **env);
int		print_env(t_list *env);
int		run_pwd(void);
int		run_cd(t_command *command, t_list *env);
int		run_echo(t_command *command);
int		run_exit(t_minishell *mini, t_command *command);
int		run_export(t_command *command, t_list *env);
int		run_unset(t_command *command, t_list *env);
int		execute(t_minishell *mini);
int		run_bins(t_minishell *mini, t_command *comm);
int		run_builtins(t_minishell *mini, t_command *command);
int		is_builtins(t_command *command);
char	*get_env_param(t_list *env, char *param);
char	*get_need_path(char *path, char *command);
int		update_env(t_list *env, char *key, char *new_line);
void	sig_handler(int sig);



#endif