#include "minishell.h"

static void	loop(t_list *token, t_list **tokens, char **result,
		t_word_desc *word)
{
	while (token && (word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		token = token->next;
		word = token->content;
		*result = str_enlarge(*result, word->word);
		*tokens = token->next;
	}
}

char	*tokens_merge(t_list **tokens, t_flg stop_on)
{
	t_list		*token;
	t_word_desc	*word;
	char		*result;

	result = NULL;
	token = *tokens;
	if (!token || (((t_word_desc *)token->content)->flags) & (T_SPEC | stop_on))
		return (NULL);
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		result = ft_strdup(word->word);
		loop(token, tokens, &result, word);
	}
	else
	{
		result = ft_strdup(word->word);
		*tokens = token->next;
	}
	return (result);
}
