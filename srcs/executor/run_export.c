/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 12:33:19 by talyx             #+#    #+#             */
/*   Updated: 2021/09/21 15:13:30 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export(t_list **env)
{
	char	*line;
	t_list	*tmp;

	tmp = *env;
	tmp = tmp->next;
	while (tmp)
	{
		line = tmp->content;
		ft_putstr("declare -x ");
		ft_putstr(line);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	return (1);
}

int	ft_error_export(char *arg, int error)
{
	int i;

	i = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	if (error == 0)
		ft_putstr_fd("\': not valid in this contex ", 2);
	else if (error == -1)
		ft_putstr_fd("\': not a valid identifier", 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int	not_env(char *arg, int j, t_list **env)
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

void	lst_update(t_list **env, char *param, int size)
{
	char	*line;

	line = malloc(sizeof(char) * size);
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
		if (ft_isalnum(arg[i]) == 0)
		{
			k = ft_error_export(arg, -1);
			break;
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
	int	j;
	int	k;

	i = 1;
	k = 1;
	while (arg[i])
	{
		j = 0;
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
		return (1);
	}
	else
		i = check_export_arg(command->arg, env);
	return (i);
}