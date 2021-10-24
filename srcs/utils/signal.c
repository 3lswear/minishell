/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:00:22 by talyx             #+#    #+#             */
/*   Updated: 2021/09/11 18:09:46 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_all_fd.end_herecode == 0)
		{
			ft_putstr("\n");
			exit(2);
		}
		else if (g_all_fd.not_line == 1)
		{
			ft_putstr("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}

}
void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		// rl_catch_signals = 0;
		if (g_all_fd.end_herecode == 0)
		{
			ft_putstr("\033[2D");
			ft_putstr("\033[K");
		}
		else if (g_all_fd.not_line == 1)
		{
			ft_putstr("\033[12D");
			ft_putstr("\033[K");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}

	}
}
