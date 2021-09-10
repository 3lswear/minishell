/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:00:22 by talyx             #+#    #+#             */
/*   Updated: 2021/09/10 17:01:19 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\033[1D");
		ft_putstr("\033[1D");
		ft_putstr("  ");
		ft_putstr("\033[1D");
		ft_putstr("\033[1D");
		ft_putstr("\n");
		ft_putstr("\033[32mminishell\033[0m \033[31m➢\033[0m ");
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr("\033[1D");
		ft_putstr("\033[1D");
		ft_putstr("  ");
		ft_putstr("\033[1D");
		ft_putstr("\033[1D");

	}
}