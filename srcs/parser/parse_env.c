/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:08:22 by talyx             #+#    #+#             */
/*   Updated: 2021/09/23 18:45:02 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_minishell *mini, char **env)
{
	int	i;

	i = 0;
	mini->env = NULL;
	ft_lstadd_back(&mini->env, ft_lstnew(""));
	while (env[i])
	{
		ft_lstadd_back(&mini->env, ft_lstnew(env[i]));
		i++;
	}
}

int		print_env(t_list *env)
{
	t_list	*tmp;
	char	*envp;

	tmp = env;
	while (tmp)
	{
		envp = tmp->content;
		if (envp && ft_strlen(envp) > 0)
		{
			ft_putstr(envp);
			ft_putstr("\n");
		}
		// else
		// 	ft_putstr_fd("error: print env\n", 2);
		tmp = tmp->next;
	}
	return (1);
}
