#include "minishell.h"

char *tokens_merge(t_list **tokens, t_flg stop_on)
{
	t_list *token;
	t_word_desc *word;
	char *result;

	result = NULL;
	(void)stop_on;
	token = *tokens;
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next &&
			!(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		result = ft_strdup(word->word);
		while (token && (word->flags & T_NOSPC) && token->next &&
				!(((t_word_desc *)token->next->content)->flags & T_SPEC))
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
	while (*tokens && (word->flags & T_SPEC) && (word->flags & T_REDIR) && (!(res.redir->in) || !(res.redir->out)
				|| !(res.append->in) || !(res.append->out)))
	{
		word = (*tokens)->content;
		redir_op = word->word;
		/* token = token->next; */
		*tokens = (*tokens)->next;
		filename = tokens_merge(tokens, 0);

		if (!ft_strncmp(redir_op, ">", 2))
			res.redir->out = filename;
		else if (!ft_strncmp(redir_op, "<", 2))
			res.redir->in = filename;
		else if (!ft_strncmp(redir_op, ">>", 2))
			res.append->out = filename;
		else if (!ft_strncmp(redir_op, "<<", 2))
			res.append->in = filename;
		/* token = token->next; */
	}
	/* if (token) */
	/* 	word = token->content; */

	return (res);
}
