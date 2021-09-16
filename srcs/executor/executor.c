/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:52:41 by talyx             #+#    #+#             */
/*   Updated: 2021/09/14 18:56:50 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//?!
int	execute(t_minishell *mini)
{
	t_list		*commands;
	t_command	*command;

	commands = mini->commands;
	while (commands)
	{
		command = commands->content;
	// if (command->red->in || command->red->out)
	// 	redirect(mini, 1);
	// else if (command->append->in || command->red->out)
	// 	redirect(mini, 2);
	// else if (command->pipe)
	// 	pipe(mini);
	if (is_builtins)
		run_builtins(mini, command);
	else
		run_bins(mini, command);
		commands = commands->next;
	}
	return (1);
}