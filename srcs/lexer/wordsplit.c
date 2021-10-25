/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:01:59 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:50:39 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	loop(int *i, char *str, t_list **tokens, int add) */
/* { */
/* 	int	j; */
/* 	int	error; */

/* 	error = 0; */
/* 	j = *i; */
/* 	while (str[j] && !in_set(&str[j], IFS) && str[j] != '\'' */
/* 		&& str[j] != '\"') */
/* 		j++; */
/* 	if (str[j] == '\'') */
/* 	{ */
/* 		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add); */
/* 		error |= handle_quote(str, &j, tokens, 0); */
/* 	} */
/* 	else if (str[j] == '\"') */
/* 	{ */
/* 		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add); */
/* 		error |= handle_dquote(str, &j, tokens, 0); */
/* 	} */
/* 	else */
/* 		word_li_append(tokens, ft_substr(str, *i, j - *i), add); */
/* 	*i = j; */
/* 	return (error); */
/* } */

static int	scroll_ifs2(char *str, int *i)
{
	int	count;

	count = 0;
	if (!str || !(*str) || !(str[*i]))
		return (0);
	while ((str[*i] == ' ') || (str[*i] == '\n') || (str[*i] == '\t'))
	{
		(*i)++;
		count++;
	}
	return (count);
}

static t_list	**append_all(t_list **tokens, char *str, int flag)
{
	word_li_append(tokens, ft_strdup(str), flag);
	return (tokens);
}

// splits by IFS, respecting quotes
t_list	**wordsplit(char *str, int flag, t_list *prev)
{
	t_list	**tokens;
	int		i;
	int		j;
	int		*prev_flg;

	tokens = ft_calloc(sizeof(t_list *), 1);
	i = 0;
	if (flag & T_DQUOTE)
		return (append_all(tokens, str, flag));
	if (prev)
		prev_flg = &((t_word_desc *)prev->content)->flags;
	if (prev && scroll_ifs2(str, &i))
		*prev_flg = (*prev_flg & (~T_NOSPC));
	while (str[i])
	{
		j = i;
		while (str[j] && !in_set(&str[j], IFS))
			j++;
		word_li_append(tokens, ft_substr(str, i, j - i), flag);
		i = j;
		if (str[j])
			i++;
	}
	return (tokens);
}
