/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:04:23 by talyx             #+#    #+#             */
/*   Updated: 2021/09/18 18:29:44 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_unset(char *arg, int error)
{
	if (error == 0)
		ft_putstr_fd("unset: not enough arguments", 2);
	else if (error == -1)
	{
		ft_putstr_fd("unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid parameter name", 2);
	}
	ft_putstr_fd("\n", 2);
	return (0);
}

int	check_arg_unset(char *arg, t_list *env)
{
	int		i;
	char	*line;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (-1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]))
			return (-1);
	}
	line = get_env_param(env, arg);
	if (!line)
		return (0);
	return (1);	
}

int	delete_env_param(char *arg, t_list **env)
{
	char	*line;
	int		i;
	t_list	*tmp;
	t_list	*prev;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		line = tmp->content;
		if (ft_strncmp(line, arg, ft_strlen(arg)))
		{
			if (i == 0)
				*env = (*env)->next;
			else
				prev = tmp->next;
			free(tmp->content);
			free(line);
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

int	run_unset(t_command *command, t_list *env)
{
	int	i;
	int	a;

	i = 0;
	if (!command->arg[0])
		return (ft_error_unset(command->arg[0], 0));
	while (command->arg[i])
	{
		a = check_arg_unset(command->arg[i], env);
		if (a == 1)
			delete_env_param(command->arg[i], &env);
		else if (a == -1)
			return(ft_error_unset(command->arg[i], -1));
		i++;
	}
	return (1);
}