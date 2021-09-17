/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 17:31:12 by talyx             #+#    #+#             */
/*   Updated: 2021/09/17 17:31:14 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_command *command)
{
	if (ft_strequ(command->path, "env"))
		return (1);
	else if (ft_strequ(command->path, "pwd"))
		return (1);
	else if (ft_strequ(command->path, "echo"))
		return (1);
	else if (ft_strequ(command->path, "export"))
		return (1);
	else if (ft_strequ(command->path, "unset"))
		return (1);
	else if (ft_strequ(command->path, "cd"))
		return (1);
	else if (ft_strequ(command->path, "exit"))
		return (1);
	return (0);
}
//!
int	run_builtins(t_minishell *mini, t_command *command)
{
	if (ft_strequ(command->path, "env"))
		return (print_env(mini->env));			//!
	else if (ft_strequ(command->path, "pwd"))
		return(run_pwd());			//!
	else if (ft_strequ(command->path, "echo"))
		return (run_echo(command));			//?
	else if (ft_strequ(command->path, "export"))
		return (run_export(mini, command));			//?
	else if (ft_strequ(command->path, "unset"))
		return (run_unset(mini, command));			//?
	else if (ft_strequ(command->path, "cd"))
		return (run_cd(mini, command));			//?
	else if (ft_strequ(command->path, "exit"))
		return (run_exit(mini, command));			//?
	return (0);
}