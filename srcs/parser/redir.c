#include "minishell.h"

t_redirects get_redir(t_list **tokens)
{
	t_redirects res;
	t_list *token;
	t_word_desc *word;
	char *filename;
	char *redir_op;

	token = *tokens;
	if (!token)
	{
		res.redir = NULL;
		res.append = NULL;
		return (res);
	}
	word = token->content;
	res.append = ft_calloc(sizeof(t_redir), 1);
	res.redir = ft_calloc(sizeof(t_redir), 1);
	while (token && (word->flags & T_SPEC) && (word->flags & T_REDIR) && (!(res.redir->in) || !(res.redir->out)
				|| !(res.append->in) || !(res.append->out)))
	{
		redir_op = word->word;
		token = token->next;
		word = token->content;
		if ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
		{
			filename = ft_strdup(word->word);
			while ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
			{
				token = token->next;
				word = token->content;
				filename = str_enlarge(filename, word->word);
				*tokens = token->next;
			}
		}
		else
		{
			filename = ft_strdup(word->word);
			*tokens = token->next;
		}

		if (!ft_strncmp(redir_op, ">", 2))
			res.redir->out = filename;
		else if (!ft_strncmp(redir_op, "<", 2))
			res.redir->in = filename;
		else if (!ft_strncmp(redir_op, ">>", 2))
			res.append->out = filename;
		else if (!ft_strncmp(redir_op, "<<", 2))
			res.append->in = filename;
		token = token->next;
	}
	if (token)
		word = token->content;

	return (res);
}
