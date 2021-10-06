/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:59:29 by talyx             #+#    #+#             */
/*   Updated: 2021/09/21 14:57:38 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char *argv[], char **env)
{
	t_minishell	mini;
	int			i;

	mini.exit = 0;
	mini.arg = argv;
	mini.envp = env;
	mini.STDin = 0;
	mini.STDout = 1;
	if (argc == 1)
	{
		parse_env(&mini, env);
		while (mini.exit != 1)
		{
			i = read_line(&mini);
			if (i == 0)
				continue ;
			parse(&mini, env);
			execute(&mini);
			free(mini.commands);
		}
	}
	(void)argv;
	return (0);
}