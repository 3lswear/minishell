/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:01:54 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:02:00 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word_desc	*wdesc_new(char *word, int flags)
{
	t_word_desc	*result;

	result = ft_calloc(sizeof(t_word_desc), 1);
	if (!result)
		return (NULL);
	result->word = word;
	result->flags = flags;
	return (result);
}
