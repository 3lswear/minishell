/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:08:22 by talyx             #+#    #+#             */
/*   Updated: 2021/09/14 15:53:43 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_minishell *mini, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(&mini->env, ft_lstnew(env[i]));
		i++;
	}
}

void	print_env(t_list *env)
{
	t_list	*tmp;
	char	*envp;

	tmp = env;
	while (tmp)
	{
		envp = tmp->content;
		ft_putstr(envp);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
