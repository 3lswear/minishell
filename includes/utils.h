#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

void	commands_free(t_list *commands);
void	word_li_free(t_list *li);
void	word_list_free(t_list **tokens);

void	word_list_print(t_list **head);

#endif
