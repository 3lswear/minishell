/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:02:41 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:02:42 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe(t_list **tokens, t_minishell *mini)
{
	int			pipe;
	t_word_desc	*word;

	(void)mini;
	pipe = 0;
	if (!tokens || !(*tokens))
		return (0);
	word = (*tokens)->content;
	while (*tokens && (word->flags & T_SPEC))
	{
		if (word->flags & T_PIPE)
		{
			pipe = 1;
			*tokens = (*tokens)->next;
			break;
		}
		(*tokens) = (*tokens)->next;
		if (*tokens)
			word = (*tokens)->content;
	}
	return (pipe);
}
