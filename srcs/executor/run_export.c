/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:19 by talyx             #+#    #+#             */
/*   Updated: 2021/09/16 18:11:19 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(t_list *env)
{
	char	*line;

	while (env)
	{
		line = env->content;
		ft_putstr("declare -x ");
		ft_putstr(line);
		ft_putstr("\n");
		env = env->next;
	}
	
}

int	ft_error_export(char *arg, int error)
{
	int i;

	i = 0;
	if (error == 0)
		ft_putstr_fd("export: not valid in this contex: ", 2);
	else if (error == -1)
		ft_putstr_fd("export: not a valid identifier: ", 2);
	while (arg[i] && (arg[i] != 0 || arg[i] != '='))
	{
		ft_putchar_fd(arg[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
	return (0);
}

int	not_env(char *arg, int j, t_list *env)
{
	char	*param;
	char	*check;
	int		i;

	i = 1;
	param = malloc (sizeof(char) * j);
	ft_strncpy(param, arg, j);
	check = get_env_param(env, param);
	if (!check)
		i = 0;
	free(param);
	return (i);
}

int	check_export_arg(char **arg, t_list *env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 1;
	while (arg[i])
	{
		j = 0;
		if (ft_isdigit(arg[i][0]) || arg[i][0] == '=')
			k = ft_error_export(arg[i], 0);
		else
		{
			while (arg[i][j] && arg[i][j] != '=')
			{
				if (ft_isalnum(arg[i][j])== 0)
				{
					k = ft_error_export(arg[i], -1);
					break;
				}
				j++;
			}
			if (arg[i][j] == '=' && !not_env(arg[i], j, env))
				ft_lstadd_back(&env, arg[i]);
		}
		i++;
	}
	return (k);
}

int	run_export(t_command *command, t_list *env)
{
	int	i;

	if (!command->arg[0])
	{
		print_export(env);
		return (1);
	}
	else
		i = check_exprot_arg(command->arg, env);
	return (i);
}