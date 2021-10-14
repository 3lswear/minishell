/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:52:41 by talyx             #+#    #+#             */
/*   Updated: 2021/09/18 18:38:12 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_minishell *mini)
{
	t_list		*commands;
	t_command	*command;
	int			pip;

	pip = 2;
	commands = mini->commands;
	while (commands)
	{
		command = commands->content;
		// if (command->red->in)
		// 	re_input(mini, command->red);
		// else if (command->append->in)
		// 	re_input(mini, command->append);
		// else if (command->red->out)
		// 	redirect(mini, command->red, 1);
		// else if (command->append->out)
		// 	redirect(mini, command->append, 2);
		// if (command->pipe)
		// 	pip = make_pipe(mini);
		// if (pip == 0)
		// {
		// 	commands = commands->next;
		// 	continue ;
		// }
		if (is_builtins(command))
			run_builtins(mini, command);
		else
			run_bins(mini, command);
		commands = commands->next;
	}
	return (1);
}