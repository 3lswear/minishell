/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:59:29 by talyx             #+#    #+#             */
/*   Updated: 2021/09/14 16:03:56 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
	t_minishell	mini;

	mini.exit = 0;
	if (argc == 1)
	{
		parse_env(&mini, env);
		while (mini.exit != 1)
		{
			read_line(&mini);
			// parse(&mini);		sunderle part
			// execute(&mini);		talyx	 part
			//free_line(&mini);
		}
		// free_and_exit(&mini);
	}
	(void)argv;
	return (0);
}