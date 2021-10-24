/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:02:22 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/24 18:17:42 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*token_get_var(t_list *token)
{
	char			*result;
	char			*str;
	unsigned int	i;
	t_word_desc		*word;

	word = token->content;
	if (word->flags & (T_NOEXP | T_SPEC))
		return (NULL);
	str = ft_strchr(word->word, '$');
	if (!str)
		return (NULL);
	i = 1;
	if (!ft_strncmp(&str[i], "?", 2))
		i = 2;
	else if (str[i] && (ft_isalpha(str[i]) || str[i] == '_'))
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	if (i == 1)
		return (NULL);
	result = ft_substr(str, 0, i);
	return (result);
}

void	split_on_vars(t_list **tokens)
{
	t_list		*li;
	t_list		*prev;
	t_word_desc	*word_desc;
	t_list		**split;
	char		*var;

	li = *tokens;
	prev = NULL;
	while (li)
	{
		var = token_get_var(li);
		word_desc = li->content;
		if (word_desc->flags & (T_NOEXP | T_SPEC) || !var)
			split = NULL;
		else
			split = ft_split2(word_desc->word, var, word_desc->flags, T_VAR);
		tokens_insert2(split, &li, &prev, tokens);
		free(split);
		free(var);
		li = li->next;
	}
}

t_list	**vars_subst_get_split(t_word_desc *word, t_minishell *mini,
		t_list *prev)
{
	char	*value;
	char	*env_val;
	t_list	**split;

	if (!ft_strncmp("$?", word->word, 3))
		value = itoa2(mini->exit_status);
	else
	{
		env_val = get_env_param(mini->env, word->word + 1);
		if (env_val)
			value = ft_strdup(env_val);
		else
			value = NULL;
	}
	if (!value && !(word->flags & T_DQUOTE))
		split = NULL;
	else if (!value)
	{
		split = ft_calloc(sizeof(t_list *), 1);
		ft_lstadd_back(split, ft_lstnew(wdesc_new(ft_strdup(""), word->flags)));
	}
	else
		split = wordsplit(value, word->flags, prev);
	if (value && DEBUG)
		fprintf(stderr, "var value is: [%s]\n", value);
	free(value);
	return (split);
}

/* returns 1 if needs to restart loop */
static int	token_del(t_list **tokens, t_list **li, t_list **prev)
{
	t_list	*tmp;

	if ((*prev))
	{
		(*prev)->next = (*li)->next;
		word_li_free((*li));
		(*li) = (*prev);
		return (0);
	}
	else
	{
		tmp = (*li);
		(*li) = (*li)->next;
		word_li_free(tmp);
		(*tokens) = (*li);
		(*prev) = NULL;
		return (1);
	}
}

/* expand vars and insert them */
void	vars_substitute(t_list **tokens, t_minishell *mini)
{
	t_list		*li;
	t_list		*prev;
	t_list		**split;

	li = *tokens;
	prev = NULL;
	while (li)
	{
		if (((t_word_desc *)li->content)->flags & T_VAR)
		{
			split = vars_subst_get_split(li->content, mini, prev);
			if (split)
				tokens_insert(split, &li, &prev, tokens);
			free(split);
			if (!split)
				if (token_del(tokens, &li, &prev))
					continue ;
		}
		if (!li)
			break ;
		prev = li;
		li = li->next;
	}
}
