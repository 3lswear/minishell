/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:11:45 by talyx             #+#    #+#             */
/*   Updated: 2021/08/15 18:11:45 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_s(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char const *s, char *set)
{
	int		count;
	int		is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (in_s(*s, set))
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	w_s(char const *s, int pos, char *set)
{
	size_t	len;

	len = 0;
	while (s[pos])
	{
		if (in_s(s[pos], set))
			return (len);
		len++;
		pos++;
	}
	return (len);
}

char	**ft_ssplit(char const *s, char *set)
{
	char		**tab;
	t_counter	c;

	c.i = -1;
	c.j = 0;
	c.k = 0;
	tab = malloc(sizeof(char *) * (count_words(s, set) + 1));
	while (s[++c.i])
	{
		if (!in_s(s[c.i], set))
		{
			if (c.k == 0)
				tab[c.j] = malloc(sizeof(char) * (w_s(s, c.i, set) + 1));
			tab[c.j][c.k] = s[c.i];
			tab[c.j][++c.k] = '\0';
		}
		if ((in_s(s[c.i], set) && !in_s(s[c.i + 1], set) && c.k > 0))
		{
			c.k = 0;
			c.j++;
		}
	}
	tab[count_words(s, set)] = NULL;
	return (tab);
}
