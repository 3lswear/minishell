#include "minishell.h"

t_word_desc	*wdesc_new(char *word, int flags)
{
	t_word_desc	*result;

	result = ft_calloc(sizeof(t_word_desc), 1);
	if (!result)
		return (NULL);
	result->word = word;
	result->flags = flags;
	return (result);
}
