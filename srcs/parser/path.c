#include "minishell.h"

char	*get_path(t_list **tokens)
{
	char		*path;
	t_list		*token;
	t_word_desc	*word;

	token = *tokens;
	if (!token)
		return (NULL);
	word = token->content;
	if (word->flags & T_SPEC)
		return (NULL);
	if (!(word->flags & T_SPEC) && (word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		path = ft_strdup(word->word);
		while ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
		{
			token = token->next;
			word = token->content;
			path = str_enlarge(path, word->word);
			*tokens = token->next;
		}
	}
	else
	{
		path = ft_strdup(word->word);
		*tokens = token->next;
	}
	
	return (path);
}
