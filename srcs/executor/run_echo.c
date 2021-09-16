/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:14:44 by talyx             #+#    #+#             */
/*   Updated: 2021/09/15 12:31:43 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_echo(t_command *command)
{
	int	i;

	i = 0;
	while (command->arg[i])
	{
		ft_putstr(command->arg[i]);
		if (command->arg[i + 1] && command->arg[i][0] != '\0')
			ft_putstr(" ");
		i++;
	}
	if (!ft_strequ(command->option, "-n"))
		ft_putstr("\n");
	return (1);	
}