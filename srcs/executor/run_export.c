/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:19 by talyx             #+#    #+#             */
/*   Updated: 2021/10/24 17:39:27 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_env(char *arg, int j, t_list **env)
{
	char	*param;
	char	*check;
	int		i;

	i = 1;
	param = ft_calloc(sizeof(char), j + 1);
	ft_strncpy(param, arg, j);
	check = get_env_param(env, param);
	if (!check)
		i = 0;
	free(param);
	return (i);
}

void	lst_update(t_list **env, char *param, int size)
{
	char	*line;

	line = ft_calloc(sizeof(char), size + 1);
	ft_strncpy(line, param, size);
	update_env(env, line, param);
	free(line);
}

int	check_export_handler(char *arg, t_list **env)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			k = ft_error_export(arg, -1);
			break ;
		}
		i++;
	}
	if (arg[i] == '=' && !not_env(arg, i, env))
		ft_lstadd_back(env, ft_lstnew(ft_strdup(arg)));
	else if (arg[i] == '=' && not_env(arg, i, env))
		lst_update(env, arg, i);
	return (k);
}

int	check_export_arg(char **arg, t_list **env)
{
	int	i;
	int	k;

	i = 1;
	k = 1;
	while (arg[i])
	{
		if (ft_isdigit(arg[i][0]) || arg[i][0] == '=')
			k = ft_error_export(arg[i], -1);
		else
			k = check_export_handler(arg[i], env);
		i++;
	}
	return (k);
}

int	run_export(t_command *command, t_list **env)
{
	int	i;

	if (!command->arg[1])
	{
		print_export(env);
		return (0);
	}
	else
		i = check_export_arg(command->arg, env);
	return (i);
}
