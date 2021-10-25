/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:02:36 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:02:37 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_list **tokens)
{
	char		*path;
	t_list		*token;
	t_word_desc	*word;

	token = *tokens;
	if (!token)
		return (NULL);
	word = token->content;
	if (word->flags & T_PIPE)
		return (NULL);
	while ((*tokens) && (word->flags & T_REDIR))
	{
		(*tokens) = (*tokens)->next;
		if (*tokens)
			word = (*tokens)->content;
	}
	path = tokens_merge(tokens, 0);
	return (path);
}
