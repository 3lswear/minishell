/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:28:57 by talyx             #+#    #+#             */
/*   Updated: 2021/09/19 17:21:18 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_param(t_list **env, char *param)
{
	t_list	*tmp;
	char	*line;
	int		len;

	tmp = *env;
	len = ft_strlen(param);
	while (tmp)
	{
		line = tmp->content;
		if (!ft_strncmp(line, param, len) && line[len] == '=')
			return(line + len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_need_path(char *path_dir, char *command)
{
	DIR				*dir;
	struct dirent	*item;
	char			*path;
	char			*tmp;

	path = NULL;
	dir = opendir(path_dir);
	if (!dir)
		return (NULL);
	item = readdir(dir);
	while (item)
	{
		if (ft_strequ(item->d_name, command))
		{
			tmp = ft_strjoin("/", command);
			path = ft_strjoin(path_dir, tmp);
			free(tmp);
			break;
		}
		item = readdir(dir);
	}
	closedir(dir);
	return (path);
}