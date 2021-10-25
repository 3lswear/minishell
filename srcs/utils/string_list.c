/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:12:44 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:12:59 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_list_free(t_list **list)
{
	t_list	*li;
	t_list	*tmp;

	li = *list;
	tmp = NULL;
	while (li)
	{
		tmp = li->next;
		free(li->content);
		free(li);
		li = NULL;
		if (tmp)
			li = tmp;
		else
			break ;
	}
}
