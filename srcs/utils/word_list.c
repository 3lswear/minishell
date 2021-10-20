#include "minishell.h"

void	word_li_append(t_list **tokens, char *word, int flag)
{
	if ((*word) || (!(*word) && (flag & (T_NOEXP | T_DQUOTE))))
		ft_lstadd_back(tokens, ft_lstnew(wdesc_new(word, flag)));
	else
	{
		free(word);
	}
}

void	delims_free(t_list **delims)
{
	t_list *delim;
	t_list *tmp;

	delim = *delims;
	while (delim)
	{
		tmp = delim->next;
		free(delim);
		delim = tmp;
	}
}

void	word_li_free(t_list *li)
{
	if (li)
	{
		free(((t_word_desc *)li->content)->word);
		free(li->content);
		free(li);
	}
}

void	word_list_free(t_list **tokens)
{
	t_list *token;
	t_list *tmp;
	t_word_desc *word;

	token = *tokens;
	while (token)
	{
		word = token->content;
		tmp = token->next;
		free(word->word);
		free(token->content);
		free(token);
		token = tmp;
	}
	*tokens = NULL;
}
