/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:57:25 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/25 15:58:07 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_free(t_list **env)
{
	t_list	*tmp;
	t_list	*next;
	char	*line;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		line = tmp->content;
		free(line);
		free(tmp);
		tmp = next;
	}
	free(env);
}
