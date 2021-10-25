/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:59:16 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 18:00:35 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "structs.h"

# include "error.h"
# include "parser.h"
# include "utils.h"

# define PIPE 	0
# define REDIR	1

# define PROMPT_OK	"🤏🐚🙂~> "
# define PROMPT_BAD	"🤏🐚🤬~> "

/* DEBUG */
# ifndef DEBUG
#  define DEBUG 0
# endif

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
void	sig_int_handler(int sig);

/* int		parse(t_minishell *mini, char **env); */
int		is_redir(t_command *command);
t_pipe	*init_pipe(int pid, int fd[2]);
int		re_input(t_minishell *mini, char *path);
int		re_output(t_minishell *mini, char *path, int type);
int		redirect(t_minishell *mini, t_command *command);
int		run_redir(t_minishell *mini, t_redir *redir, int flag);
int		run_heredoc(t_minishell *mini, char *eof);
void	run_heredoc_chile(t_minishell *mini, char *eof);
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
