/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:59:11 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 17:59:12 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

# define T_NOEXP		0b00000001
# define T_NOSPC		0b00000010
# define T_DQUOTE		0b00000100
# define T_VAR			0b00001000
# define T_ASSIGN		0b00010000
# define T_SPEC			0b00100000
# define T_REDIR		0b01000000
# define T_PIPE			0b10000000

# define IFS	" \t\n"

typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

typedef struct s_redirects
{
	t_redir	*append;
	t_redir	*redir;
}	t_redirects;

typedef struct s_split
{
	const char	*delim;
	int			delim_len;
	const char	*str;
	int			len;
	char		*substr;
}	t_split;

typedef struct s_flags
{
	int	flag;
	int	f_spec;
}	t_flags;

typedef int	t_flg;

/* main parse block */
int			parse(t_minishell *mini);
char		*get_path(t_list **tokens);
int			*tokens_del_redirs(t_list **redir_token);
t_redirects	get_redir(t_list *token, t_minishell *mini);
char		**get_args(t_list **tokens, char *path);
int			get_pipe(t_list **tokens, t_minishell *mini);

/* first_pass */
t_list		**first_pass(char *str, t_minishell *mini, int flag_add);
void		handle_dollar(char *str, int *i, t_list *tokens);
int			handle_dquote(char *str, int *i, t_list **tokens, int flag_add);
int			handle_quote(char *str, int *i, t_list **tokens, int flag_add);
int			in_set(char *chr, const char *special);
void		scroll_ifs(char *str, int *i);
t_list		**wordsplit(char *str, int add, t_list *prev);

/* lexer */
t_list		**string_tokenize(t_minishell *state);
void		handle_assignment(t_list **tokens);
void		word_li_append(t_list **tokens, char *word, int flag);

/* vars */
void		tokens_insert(t_list **split, t_list **li, t_list **prev,
				t_list **tokens);
void		tokens_insert2(t_list **split, t_list **li, t_list **prev,
				t_list **tokens);
void		split_on_vars(t_list **tokens);
void		vars_substitute(t_list **tokens, t_minishell *mini);

/* general */
char		*tokens_merge(t_list **tokens, t_flg stop_on);
void		validity_check(t_list **commands, t_minishell *mini);

t_word_desc	*wdesc_new(char *word, int flags);
t_list		**ft_split2(char const *s, const char *delim, int flags,
				int spec_flg);

#endif
