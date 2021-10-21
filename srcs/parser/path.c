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
	path = tokens_merge(tokens, 0);
	
	return (path);
}
