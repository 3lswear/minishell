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
	if (word->flags & T_PIPE)
		return (NULL);
	while ((*tokens) && (word->flags & T_REDIR))
	{
		(*tokens) = (*tokens)->next;
		if (*tokens)
			word = (*tokens)->content;
	}
	path = tokens_merge(tokens, 0);
	return (path);
}
