#include "minishell.h"

char	*tokens_merge(t_list **tokens, t_flg stop_on)
{
	t_list		*token;
	t_word_desc	*word;
	char		*result;

	result = NULL;
	(void)stop_on;
	token = *tokens;
	if (!token)
		return (NULL);
	word = token->content;
	if (word->flags & T_SPEC)
		return (NULL);
	if ((word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		result = ft_strdup(word->word);
		while (token && (word->flags & T_NOSPC) && token->next
			&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
		{
			token = token->next;
			word = token->content;
			result = str_enlarge(result, word->word);
			*tokens = token->next;
		}
	}
	else
	{
		result = ft_strdup(word->word);
		*tokens = token->next;
	}
	return (result);
}
