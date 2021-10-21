#include "minishell.h"

int	get_pipe(t_list **tokens, t_minishell *mini)
{
	int			pipe;
	t_word_desc	*word;

	(void)mini;
	pipe = 0;
	if (!tokens || !(*tokens))
		return (0);
	word = (*tokens)->content;
	if ((*tokens))
	{
		if ((word->flags & T_SPEC) && (!ft_strncmp(word->word, "|", 2)))
		{
			pipe = 1;
			*tokens = (*tokens)->next;
		}
		else
			pipe = 0;
	}
	else
		pipe = 0;
	return (pipe);
}
