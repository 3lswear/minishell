/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 17:58:55 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:49:12 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

char	*itoa2(int n);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*str_enlarge(char *orig, char *add);
char	*heredoc_subst(char *input, t_minishell *mini);

/* free */
void	commands_free(t_list *commands);
void	word_li_free(t_list *li);
void	word_list_free(t_list **tokens);
void	delims_free(t_list **delims);

/* debug funcs */
char	*get_flag_name(int flag);
void	strarr_print(char **arr);
void	cmd_print(t_command *cmd);
void	commands_print(t_list **cmds);
void	word_list_print(t_list **head);
char	*get_flag_name(int flag);
void	word_list_print(t_list **head);

void	string_list_print(t_list **list, char *prefix);
void	string_list_free(t_list **list);

#endif
