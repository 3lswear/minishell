/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:17:37 by talyx             #+#    #+#             */
/*   Updated: 2021/09/16 12:10:48 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_list *env, char *key, char *new_line)
{
	t_list	*tmp;
	t_list	*new;
	char	*line;

	tmp = env;
	while (tmp)
	{
		line = tmp->content;
		if (ft_strncmp(line, key, ft_strlen(key)))
		{
			new = ft_lstnew(new_line);
			env->next = new;
			new->next = tmp->next;
			return (1);
		}
		env = tmp;
		tmp = tmp->next;
	}
	return (0);	
}

int	update_old(t_list *env)
{
	char	arr[4096];
	char	*old;

	if (!getcwd(arr, 4096))
		return (0);
	old = ft_strjoin("OLDPWD=", arr);
	if (!old)
		return (0);
	update_env(env, "OLDPWD", old);
	free(old);
	return (1);
}

int	cd_home(t_list *env)
{
	char	*path;
	int		i;

	update_old(env);		// ?
	path = get_env_param(env, "HOME");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (0);
	}
	i = chdir(path);
	free(path);
	return (i);
}

int	cd_old(t_list *env)
{
	char	*path;
	int		i;

	path = get_env_param(env, "OLDPWD");
	if (!path)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set", 2);
		return (0);
		update_old(env);
	}
	i = chdir(path);
	free(path);
	return (i);
}

int	run_cd(t_command *command, t_list *env)
{
	int	i;

	if (!command->arg[0])
		return (cd_home(env));
	if (ft_strequ(command->arg[0], "-"))
		return (cd_old(env));
	else
	{
		update_old(env);
		i = chdir(command->arg[1]);
		if (i < 0)
			i *= -1;
		if (i != 0)
			cd_error(command->arg);
	}
	return (i);
}