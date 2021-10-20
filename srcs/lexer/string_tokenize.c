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

}

void	split_on_special(t_list **tokens, t_list **delims, int spec_flg)
{
	t_list *li;
	t_list *delim;
	t_list *prev;
	t_word_desc *word_desc;
	t_list **split;

	delim = *delims;
	while (delim)
	{
		li = *tokens;
		prev = NULL;
		while (li)
		{
			word_desc = li->content;
			if (word_desc->flags & (T_DQUOTE | T_NOEXP | T_SPEC))
				split = NULL;
			else
				split = ft_split2(word_desc->word, delim->content, word_desc->flags, spec_flg);
			tokens_insert(split, &li, &prev, tokens);
			free(split);
			li = li->next;
		}
		delim = delim->next;
	}
}

t_list **string_tokenize(t_minishell *state)
{
	t_list **tokens;
	t_list *delims;

	delims = NULL;

	tokens = first_pass(state->line, 0);

	if (DEBUG)
	{
		fprintf(stderr, "=== after first_pass: ===\n");
		word_list_print(tokens);
	}

	ft_lstadd_back(&delims, ft_lstnew("|"));
	split_on_special(tokens, &delims, T_SPEC);
	delims_free(&delims);

	delims = NULL;
	ft_lstadd_back(&delims, ft_lstnew("<<"));
	ft_lstadd_back(&delims, ft_lstnew(">>"));
	ft_lstadd_back(&delims, ft_lstnew(">"));
	ft_lstadd_back(&delims, ft_lstnew("<"));
	split_on_special(tokens, &delims, T_SPEC | T_REDIR);
	delims_free(&delims);

	if (DEBUG)
	{
		fprintf(stderr, "=== after split_on_special: ===\n");
		word_list_print(tokens);
	}

	split_on_vars(tokens);

	if (DEBUG)
	{
		fprintf(stderr, "=== after split_on_vars: ===\n");
		word_list_print(tokens);
	}

	/* word_list_free(tokens); */
	/* free(tokens); */

	return (tokens);
}
