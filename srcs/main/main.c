/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:59:29 by talyx             #+#    #+#             */
/*   Updated: 2021/10/08 16:13:17 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_minishell	mini;
	int			i;

	mini.exit = 0;
	if (argc == 1)
	{
		parse_env(&mini, env);
		while (mini.exit != 1)
		{
			i = read_line(&mini);
			if (i == 0)
				continue ;
			parse(&mini);
			execute(&mini);
			// free(mini.commands);
		}
	}
	(void)argv;
	return (0);
}
