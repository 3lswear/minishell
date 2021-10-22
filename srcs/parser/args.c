#include "minishell.h"

/* static size_t	args_count(t_list *arg_tok) */
/* { */
/* 	size_t		result; */
/* 	t_word_desc	*word; */

/* 	result = 0; */
/* 	while (arg_tok) */
/* 	{ */
/* 		word = arg_tok->content; */
/* 		if (word->flags & T_PIPE) */
/* 			break ; */
/* 		else if ((word->flags & T_NOSPC) && arg_tok->next) */
/* 		{ */
/* 			if (((t_word_desc *)arg_tok->next->content)->flags & T_SPEC) */
/* 			{ */
/* 				result++; */
/* 				break ; */
/* 			} */
/* 		} */
/* 		else if (!(word->flags & T_NOSPC) || !(arg_tok->next)) */
/* 			result++; */

/* 		arg_tok = arg_tok->next; */
/* 	} */
/* 	return (result); */
/* } */


static size_t	args_count(t_list *arg_tok)
{
	t_word_desc *word;
	size_t result;

	result = 0;
	if (!arg_tok || (((t_word_desc *)arg_tok->content)->flags) & T_SPEC)
		return (0);
	word = arg_tok->content;
	if ((word->flags & T_NOSPC) && arg_tok->next
			&& !(((t_word_desc *)arg_tok->next->content)->flags & T_SPEC))
	{
		result++;
		while (arg_tok && (word->flags & T_NOSPC) && arg_tok->next
				&& !(((t_word_desc *)arg_tok->next->content)->flags & T_SPEC))
		{
			arg_tok = arg_tok->next;
			word = arg_tok->content;
			result++;
		}
	}
	else
	{
		result++;
		arg_tok = arg_tok->next;
	}
	return (result);
}

char	**get_args(t_list **tokens, char *path)
{
	size_t		arg_num;
	char		**result;
	size_t		i;
	char		*tmp;

	arg_num = args_count(*tokens);
	if (DEBUG)
		fprintf(stderr, "arg count is [%lu]\n", arg_num);
	result = ft_calloc(sizeof(char *), arg_num + 2);
	result[0] = path;
	if (!(*tokens) || ((t_word_desc *)(*tokens)->content)->flags & T_SPEC)
		return (result);
	i = 1;
	while (i <= arg_num && !(((t_word_desc *)(*tokens)->content)->flags & T_PIPE))
	{
		while (*tokens && ((t_word_desc *)(*tokens)->content)->flags & T_REDIR)
			(*tokens) = (*tokens)->next;
		tmp = tokens_merge(tokens, 0);
		result[i] = tmp;
		i++;
		if (!(*tokens))
			break;
	}
	return (result);
}
