/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:01:49 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/25 15:51:13 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_on_special(t_list **tokens, t_list **delims, int spec_flg)
{
	t_list		*li;
	t_list		*delim;
	t_list		*prev;
	t_word_desc	*word_desc;
	t_list		**split;

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
				split = ft_split2(word_desc->word, delim->content,
						word_desc->flags, spec_flg);
			tokens_insert(split, &li, &prev, tokens);
			free(split);
			li = li->next;
		}
		delim = delim->next;
	}
}

t_list	**string_tokenize(t_minishell *state)
{
	t_list	**tokens;
	t_list	*delims;

	delims = NULL;
	tokens = first_pass(state->line, state, 0);
	ft_lstadd_back(&delims, ft_lstnew("|"));
	split_on_special(tokens, &delims, T_SPEC | T_PIPE);
	delims_free(&delims);
	delims = NULL;
	ft_lstadd_back(&delims, ft_lstnew("<<"));
	ft_lstadd_back(&delims, ft_lstnew(">>"));
	ft_lstadd_back(&delims, ft_lstnew(">"));
	ft_lstadd_back(&delims, ft_lstnew("<"));
	split_on_special(tokens, &delims, T_SPEC | T_REDIR);
	delims_free(&delims);
	split_on_vars(tokens);
	return (tokens);
}
