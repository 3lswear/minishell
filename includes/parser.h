#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

# define T_NOEXP		0b00000001
# define T_NOSPC		0b00000010
# define T_DQUOTE		0b00000100
# define T_VAR			0b00001000
# define T_ASSIGN		0b00010000
# define T_SPEC			0b00100000

typedef struct s_word_desc
{
	char	*word;
	int		flags;
}	t_word_desc;

void	parse(t_minishell *mini);
t_list	**string_tokenize(t_minishell *state);
void	handle_assignment(t_list **tokens);

t_word_desc *wdesc_new(char *word, int flags);
t_list	**ft_split2(char const *s, const char *delim, int flags, int spec_flg);


char	*ft_strjoin2(char const *s1, char const *s2);
#endif
