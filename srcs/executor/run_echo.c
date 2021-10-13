/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:14:44 by talyx             #+#    #+#             */
/*   Updated: 2021/09/19 18:28:12 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_echo(t_command *command)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	while (command->arg[i])
	{
		if (ft_strequ("-n", command->arg[i]))
			newline = 1;
		else
		{
			ft_putstr(command->arg[i]);
			if (command->arg[i + 1] && command->arg[i][0] != '\0')
				ft_putstr(" ");
		}
		i++;
	}
	if (!newline)
		ft_putstr("\n");
	return (1);	
}