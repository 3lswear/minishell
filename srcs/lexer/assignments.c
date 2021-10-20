#include "minishell.h"

void	split_on_eq(t_list **tokens)
{
	t_list *li;
	t_list *prev;
	t_word_desc *word_desc;
	t_list **split;

	li = *tokens;
	/* fprintf(stderr, "t_assign = 0x%X\n", T_ASSIGN); */
	while (li)
	{
		word_desc = li->content;
		if (word_desc->flags & (T_DQUOTE | T_NOEXP))
			split = NULL;
		else
			split = ft_split2(word_desc->word, "=", T_ASSIGN | word_desc->flags, 0);
		if (!split)
			prev = li;
		else if (!prev)
		{
			ft_lstadd_back(split, li->next);
			word_li_free(*tokens);

			*tokens = *split;
			li = ft_lstlast(*split);
			prev = li;
		}
		else
		{
			li = ft_lstlast(*split);
			ft_lstadd_back(split, prev->next->next);
			word_li_free(prev->next);
			prev->next = *split;
			prev = li;
		}
		free(split);
		li = li->next;
	}
}

int	assignment_test(t_list **tokens)
{
	t_list *token;
	t_list **split;
	t_word_desc *word;
	int result;

	token = *tokens;
	word = token->content;
	result = 0;

	if (word->flags & (T_DQUOTE | T_NOEXP | T_SPEC))
		split = NULL;
	else
		split = ft_split2(word->word, "=", word->flags, 0);

	if (split && (*split) && (*split)->next)
	{
		if (!ft_strncmp(((t_word_desc *)(*split)->content)->word, "=", 2))
			result = 0;
		else
			result = 1;
		word_list_free(split);
	}
	else
		result = 0;
	free(split);

	return(result);
}

void	handle_assignment(t_list **tokens)
{
	t_list_vars **vars;
	int result;

	result = assignment_test(tokens);

	if (DEBUG)
	{
		if (result)
		{
			fprintf(stderr, ">>> yes assignment <<<\n");
		}
		else
			fprintf(stderr, ">>> no assignment <<<\n");
	}


	(void)vars;
	/* split_on_eq(tokens); */
}
