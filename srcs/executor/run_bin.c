/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:55:37 by talyx             #+#    #+#             */
/*   Updated: 2021/09/15 11:50:47 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cmd(char *path, char *arg, t_list *env, t_minishell *mini)
{
	
}

//?
int	run_bins(t_minishell *mini, t_command *comm)
{
	char	**all_path;
	char	*path;
	char	*env;
	int		i;

	path = NULL;
	i = 0;
	env = get_env_param(mini->env, "PAHT");			//?
	if (!env)
		return(run_cmd(comm->path, comm->arg, mini->env, mini));			//?
	all_path = ft_split(env, ':');
	while (all_path[i] && path == NULL)
		path = get_need_path(all_path[i++], comm->path);
	if (path)
		i = run_cmd(path, comm->arg, mini->env, mini);
	else
		i = run_cmd(comm->path, comm->arg, mini->env, mini);
	ft_split_clear(all_path);
	free(path);
	free(env);
	return (i);
}