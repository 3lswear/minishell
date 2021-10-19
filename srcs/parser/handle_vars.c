#include "minishell.h"

/* same as tokens_insert, but make li first in split */
void	tokens_insert2(t_list **split, t_list **li, t_list **prev, t_list **tokens)
{
	if (!split)
		(*prev) = (*li);
	else if (!(*prev))
	{
		ft_lstadd_back(split, (*li)->next);
		word_li_free(*tokens);
		*tokens = *split;
		/* (*li) = ft_lstlast(*split); */
		(*li) = (*split);
		(*prev) = (*li);
	}
	else
	{
		/* (*li) = ft_lstlast(*split); */
		(*li) = (*split);
		ft_lstadd_back(split, (*prev)->next->next);
		word_li_free((*prev)->next);
		(*prev)->next = *split;
		(*prev) = (*li);
	}
}

char *token_get_var(t_list *token)
{
	char *result;
	char *str;
	unsigned int i;
	t_word_desc *word;

	word = token->content;
	if (word->flags & (T_NOEXP | T_SPEC))
		return (NULL);
	str = ft_strchr(word->word, '$');
	if (!str)
		return (NULL);
	i = 1;
	if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	if (i == 1)
		return (NULL);
	result = ft_substr(str, 0, i);
	return (result);
}

void	split_on_vars(t_list **tokens)
{
	t_list *li;
	t_list *prev;
	t_word_desc *word_desc;
	t_list **split;
	char *var;

	li = *tokens;
	prev = NULL;
	while (li)
	{
		var = token_get_var(li);
		word_desc = li->content;
		if (word_desc->flags & (T_NOEXP | T_SPEC) || !var)
			split = NULL;
		else
			split = ft_split2(word_desc->word, var, word_desc->flags & (~T_NOSPC), T_VAR);
		tokens_insert2(split, &li, &prev, tokens);
		free(split);
		free(var);
		li = li->next;
	}
}

/* if-else-if-else statement to insert split in tokens, pass &li and &prev */
void	tokens_insert(t_list **split, t_list **li, t_list **prev, t_list **tokens)
{
	if (!split)
		(*prev) = (*li);
	else if (!(*prev))
	{
		ft_lstadd_back(split, (*li)->next);
		word_li_free(*tokens);
		*tokens = *split;
		(*li) = ft_lstlast(*split);
		(*prev) = (*li);
	}
	else
	{
		(*li) = ft_lstlast(*split);
		ft_lstadd_back(split, (*prev)->next->next);
		word_li_free((*prev)->next);
		(*prev)->next = *split;
		(*prev) = (*li);
	}
}

void	vars_substitute(t_list **tokens, t_list **env)
{
	t_list *li;
	t_list *prev;
	t_word_desc *word;
	char *env_name;
	char *value;
	t_list **split;

	li = *tokens;
	prev = NULL;
	while (li)
	{
		word = li->content;
		if (word->flags & T_VAR)
		{
			env_name = word->word + 1;
			value = get_env_param(env, env_name);
			if (!value)
				split = NULL;
			else
				split = first_pass(value, word->flags);
			/* fprintf(stderr, "[%s] = [%s]\n", env_name, value); */
			tokens_insert(split, &li, &prev, tokens);
		}
		prev = li;
		li = li->next;
	}
}
