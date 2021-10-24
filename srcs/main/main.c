/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:59:29 by talyx             #+#    #+#             */
/*   Updated: 2021/10/24 18:20:41 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_minishell	mini;
	int			i;

	mini.exit = 0;
	mini.exit_status = 0;
	if (argc == 1)
	{
		parse_env(&mini, env);
		while (mini.exit != 1)
		{
			init_fd();
			i = read_line(&mini);
			if (i == 0)
				continue ;
			if (!parse(&mini))
				execute(&mini);
			else
				mini.exit_status = mini.parse_status;
			commands_free(mini.commands);
			free(mini.line);
		}
		env_free(mini.env);
	}
	(void)argv;
	return (mini.exit_status);
}
