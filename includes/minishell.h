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
# include <errno.h>
# include <sys/wait.h>

# include "libft.h"

# define PIPE 	0
# define REDIR	1

# define PROMPT_OK	"🤏🐚🙂~> "
# define PROMPT_BAD	"🤏🐚🤬~> "

/* DEBUG */
# ifndef DEBUG
#  define DEBUG 0
# endif

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
	char	*line;
	char	**arg;
	char	**envp;
	t_list	*commands;
	t_list	**env;
	char	*prompt;
}				t_minishell;

# include "error.h"
# include "parser.h"
# include "list2.h"
# include "utils.h"

t_fd	g_all_fd;

int		ft_strlen2(char **str);
int		read_line(t_minishell *mini);
void	parse_env(t_minishell *mini, char **env);
int		print_env(t_list **env);
int		run_pwd(void);
int		run_cd(t_command *command, t_list **env);
int		run_echo(t_command *command);
int		run_exit(t_minishell *mini, t_command *command);
int		run_export(t_command *command, t_list **env);
int		run_unset(t_command *command, t_list **env);
int		execute(t_minishell *mini);
int		run_bins(t_minishell *mini, t_command *comm);
int		run_builtins(t_minishell *mini, t_command *command);
int		is_builtins(t_command *command);
char	*get_env_param(t_list **env, char *param);
char	*get_need_path(char *path, char *command);
int		update_env(t_list **env, char *key, char *new_line);
void	sig_handler(int sig);

/* int		parse(t_minishell *mini, char **env); */
int		is_redir(t_command *command);
int		re_input(t_minishell *mini, char *path);
int		re_output(t_minishell *mini, char *path, int type);
int		redirect(t_minishell *mini, t_command *command);
int		run_redir(t_minishell *mini, t_redir *redir, int flag);
int		run_heredoc(char *eof);
int		run_heredoc_chile(char *eof);
int		make_pipe(t_minishell *mini);
void	env_free(t_list **env);
void	init_fd(void);
void	reset_fd(void);
void	close_fd(void);
void	close_and_reset_all(void);
void	close_and_reset_out(void);
char	*get_pwd(void);
int		update_pwd(t_list **env);
int		print_export(t_list **env);
int		ft_atoi2(const char *nptr);

#endif
