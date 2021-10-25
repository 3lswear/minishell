/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:01:15 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/24 19:49:03 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_set(char *chr, const char *special)
{
	char	*special_copy;

	special_copy = (char *)special;
	while (*special_copy)
	{
		if (*chr == *special_copy)
			return (1);
		else
			special_copy++;
	}
	return (0);
}

int	is_sep(char *chr)
{
	return (*chr == '|' || *chr == ' ' || *chr == '>' || *chr == '<');
}

void	scroll_ifs(char *str, int *i)
{
	if (!str || !(*str) || !(str[*i]))
		return ;
	while ((str[*i] == ' ') || (str[*i] == '\n') || (str[*i] == '\t'))
	{
		(*i)++;
	}
}

static int	loop(int *i, char *str, t_list **tokens, int add)
{
	int	j;
	int	error;

	error = 0;
	j = *i;
	while (str[j] && !in_set(&str[j], IFS) && str[j] != '\''
		&& str[j] != '\"')
		j++;
	if (str[j] == '\'')
	{
		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add);
		error |= handle_quote(str, &j, tokens, 0);
	}
	else if (str[j] == '\"')
	{
		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add);
		error |= handle_dquote(str, &j, tokens, 0);
	}
	else
		word_li_append(tokens, ft_substr(str, *i, j - *i), add);
	*i = j;
	return (error);
}

// splits by IFS, respecting quotes
t_list	**first_pass(char *str, t_minishell *mini, int add)
{
	t_list	**tokens;
	int		i;
	int		error;

	tokens = ft_calloc(sizeof(t_list *), 1);
	i = 0;
	error = 0;
	while (str[i])
	{
		scroll_ifs(str, &i);
		while (str[i] && !error)
		{
			scroll_ifs(str, &i);
			error |= handle_quote(str, &i, tokens, add);
			error |= handle_dquote(str, &i, tokens, add);
			scroll_ifs(str, &i);
			if (!str[i])
				break ;
			error = loop(&i, str, tokens, add);
			scroll_ifs(str, &i);
		}
		if (error)
			mini->parse_status = error;
	}
	return (tokens);
}
