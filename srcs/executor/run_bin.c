/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:55:37 by talyx             #+#    #+#             */
/*   Updated: 2021/09/17 19:56:35 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_char(t_list *env)
{
	char	**ret;
	char	*line;
	int		len;
	int		j;

	j = 0;
	len = ft_lstsize(env);
	ret = malloc(sizeof(char *) * (len + 1));
	while (env)
	{
		line = env->content;
		ret[j++] = ft_substr(len, 0, ft_strlen(len));
		env = env->next;
	}
	return (ret);	
}

int		check_dir(char *path)
{
	DIR	*dir;
	int	fd;
	int	i;

	fd = open(path, O_WRONLY);
	dir = opendir(path);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (!ft_strchr(path, '/'))
		ft_putstr_fd(": command not found\n", 2);
	else if (fd == -1 && dir == NULL)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (fd == -1 && dir != NULL)
		ft_putstr_fd(": is a directory", 2);
	else if (fd != -1 && dir == NULL)
		ft_putstr_fd(": Permission denied\n", 2);
	if (dir)
		closedir(dir);
	close(fd);
	return (0);
	
}

int	run_cmd(char *path, char **arg, t_minishell *mini)
{
	char	**envp;
	int		exit_status;
	int		pid;

	envp = lst_to_char(mini->env);
	exit_status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (exit_status)
			execve(path, arg, envp);
		exit_status = check_dir(path);
		ft_split_clear(envp);
		exit(exit_status);
	}
	else
		waitpid(pid, &exit_status, 0);
	return (exit_status);
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
		return(run_cmd(comm->path, comm->arg, mini));			//?
	all_path = ft_split(env, ':');
	while (all_path[i] && path == NULL)
		path = get_need_path(all_path[i++], comm->path);
	if (path)
		i = run_cmd(path, comm->arg, mini);
	else
		i = run_cmd(comm->path, comm->arg, mini);
	ft_split_clear(all_path);
	free(path);
	free(env);
	return (i);
} 