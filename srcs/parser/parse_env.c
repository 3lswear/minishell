/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:08:22 by talyx             #+#    #+#             */
/*   Updated: 2021/09/10 18:19:36 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_minishell *mini, char **env)
{
	int		i;
	t_env	*next;

	i = 0;
	next = malloc(sizeof(t_env));
	if (!next)
		exit(1);
	mini->env = next;
	while (env[i])
	{
		if (env[i + 1])
		{
			next->next = malloc(sizeof(t_env));
			if (!next)
				exit(1);
		}
		next->value = env[i];
		if (!env[i + 1])
			next->next = NULL;
		else
			next = next->next;
		i++;
	}
}