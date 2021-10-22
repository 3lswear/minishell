#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

char	*itoa2(int n);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*str_enlarge(char *orig, char *add);

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

#endif
