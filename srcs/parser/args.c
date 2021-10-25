/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:02:17 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/25 15:52:44 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_nospace(t_list **tok, size_t *result)
{
	t_word_desc	*word;

	word = (*tok)->content;
	while ((*tok) && !(word->flags & T_SPEC) && (word->flags & T_NOSPC)
		&& (*tok)->next
		&& !(((t_word_desc *)(*tok)->next->content)->flags & T_SPEC))
	{
		(*tok) = (*tok)->next;
		word = (*tok)->content;
	}
	(*result)++;
}

static size_t	args_count(t_list *arg_tok)
{
	t_word_desc	*word;
	size_t		result;

	result = 0;
	if (!arg_tok || (((t_word_desc *)arg_tok->content)->flags) & T_SPEC)
		return (0);
	word = arg_tok->content;
	while (arg_tok && !(word->flags & T_PIPE))
	{
		if ((word->flags & T_NOSPC) && !(word->flags & T_SPEC) && arg_tok->next
			&& !(((t_word_desc *)arg_tok->next->content)->flags & T_SPEC))
			loop_nospace(&arg_tok, &result);
		else if (!(word->flags & T_SPEC))
			result++;
		arg_tok = arg_tok->next;
		if (arg_tok)
			word = arg_tok->content;
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
	result = ft_calloc(sizeof(char *), arg_num + 2);
	result[0] = path;
	if (!(*tokens) || ((t_word_desc *)(*tokens)->content)->flags & T_SPEC)
		return (result);
	i = 1;
	while (i <= arg_num && !(((t_word_desc *)(*tokens)->content)->flags
		& T_PIPE))
	{
		while (*tokens && ((t_word_desc *)(*tokens)->content)->flags & T_REDIR)
			(*tokens) = (*tokens)->next;
		tmp = tokens_merge(tokens, 0);
		result[i] = tmp;
		i++;
		if (!(*tokens))
			break ;
	}
	return (result);
}
