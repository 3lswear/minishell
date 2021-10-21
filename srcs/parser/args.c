#include "minishell.h"

static size_t	args_count(t_list *arg_tok)
{
	size_t		result;
	t_word_desc	*word;

	result = 0;
	while (arg_tok)
	{
		word = arg_tok->content;
		/* if current token is special symbol */
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
	t_word_desc	*word;
	t_list		*token;
	size_t		i;
	char		*tmp;

	token = *tokens;
	arg_num = args_count(*tokens);
	if (DEBUG)
		fprintf(stderr, "arg count is [%lu]\n", arg_num);
	result = ft_calloc(sizeof(char *), arg_num + 2);
	result[0] = path;
	//add args to result[x], combining if no space between
	token = *tokens;
	if (!token || ((t_word_desc *)token->content)->flags & T_SPEC)
		return (result);
	i = 1;
	while (i <= arg_num)
	{
		word = token->content;
		if ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
		{
			tmp = ft_strdup(word->word);
			while ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
			{
				token = token->next;
				word = token->content;
				tmp = str_enlarge(tmp, word->word);
			}
			token = token->next;
			*tokens = token;
		}
		else
		{
			tmp = ft_strdup(word->word);
			token = token->next;
			*tokens = token;
		}
		result[i] = tmp;
		i++;
	}
	return (result);
}
