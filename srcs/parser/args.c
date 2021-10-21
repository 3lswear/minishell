#include "minishell.h"

static size_t	args_count(t_list *arg_tok)
{
	size_t		result;
	t_word_desc	*word;

	result = 0;
	while (arg_tok)
	{
		word = arg_tok->content;
		if (word->flags & T_SPEC)
			break ;
		else if ((word->flags & T_NOSPC) && arg_tok->next)
		{
			if (((t_word_desc *)arg_tok->next->content)->flags & T_SPEC)
			{
				result++;
				break ;
			}
		}
		else
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
	while (i <= arg_num)
	{
		tmp = tokens_merge(tokens, 0);
		result[i] = tmp;
		i++;
	}
	return (result);
}
