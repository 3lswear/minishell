/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:13:12 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:17:50 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop(t_list *token, t_list **tokens, char **result,
		t_word_desc *word)
{
	while (token && (word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		token = token->next;
		word = token->content;
		*result = str_enlarge(*result, word->word);
		*tokens = token->next;
	}
}

/* merge tokens when there is no space between,
 * stop_on is broken */

char	*tokens_merge(t_list **tokens, t_flg stop_on)
{
	t_list		*token;
	t_word_desc	*word;
	char		*result;

	result = NULL;
	token = *tokens;
	if (!token || (((t_word_desc *)token->content)->flags) & (T_SPEC | stop_on))
		return (NULL);
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		result = ft_strdup(word->word);
		loop(token, tokens, &result, word);
	}
	else
	{
		result = ft_strdup(word->word);
		*tokens = token->next;
	}
	return (result);
}

static void	free_nospace(t_list **tmp, t_list **token)
{
	(*tmp) = (*token)->next;
	word_li_free(*token);
	(*token) = (*tmp);
}

/* delete tokens with same logic as tokens_merge */
int	*tokens_del_redirs(t_list **redir_token)
{
	t_list		*token;
	t_list		*tmp;
	t_word_desc	*word;

	token = (*redir_token)->next;
	if (!token || !((((t_word_desc *)(*redir_token)->content)->flags)
		& T_REDIR))
		return (NULL);
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next
		&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		while (token && (word->flags & T_NOSPC) && token->next
			&& !(((t_word_desc *)token->next->content)->flags & T_SPEC))
			free_nospace(&tmp, &token);
		(*redir_token)->next = tmp;
	}
	else if (!(word->flags & (T_NOSPC | T_SPEC)))
	{
		tmp = token->next;
		word_li_free(token);
		(*redir_token)->next = tmp;
	}
	return (0);
}
