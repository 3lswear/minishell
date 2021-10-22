/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:04:43 by talyx             #+#    #+#             */
/*   Updated: 2021/09/19 13:52:32 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && (str[i] == '-' || str[i] == '+'))
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	run_exit(t_minishell *mini, t_command *command)
{
	int	count;

	count = ft_strlen2(command->arg) - 1;
	mini->exit = 1;
	mini->exit_status = 0;
	ft_putstr_fd("exit", 2);
	if (count > 1)
	{
		mini->exit_status = 1;
		ft_putstr_fd("minishell: exit: too many argument", 2);
	}
	else if (count == 1)
	{
		if (str_is_num(command->arg[1]))
			mini->exit_status = ft_atoi2(command->arg[1]);
		else
		{
			mini->exit_status = 255;
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(command->arg[1], 2);
			ft_putstr_fd(": numeric argument required", 2);
		}
	}
	ft_putstr_fd("\n", 2);
	return (mini->exit_status % 256);
}
