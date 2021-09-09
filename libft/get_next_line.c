/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:14:31 by talyx             #+#    #+#             */
/*   Updated: 2021/09/07 21:16:16 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	put_remainder(char *tmp, char **remainder)
{
	*tmp++ = '\0';
	*remainder = ft_strdup(tmp);
	return (1);
}

static int	first_try(t_gnl *gnl, char **remainder, char **line)
{
	gnl->byte_read = read(gnl->fd, gnl->buf, BUFFER_SIZE);
	if (gnl->byte_read == -1)
		return (-1);
	else
	{
		if (!*line)
			*line = ft_strdup("");
		while (gnl->byte_read > 0 && gnl->rp == 0)
		{
			gnl->buf[gnl->byte_read] = '\0';
			gnl->tmp = ft_strchr(gnl->buf, '\n');
			if (gnl->tmp)
				gnl->rp = put_remainder(gnl->tmp, remainder);
			gnl->tmp = *line;
			*line = ft_strjoin(*line, gnl->buf);
			if (!(*line))
				return (-1);
			free(gnl->tmp);
			if (gnl->rp != 1)
				gnl->byte_read = read(gnl->fd, gnl->buf, BUFFER_SIZE);
		}
		if (gnl->rp == 0 && gnl->byte_read == 0)
			return (0);
		return (1);
	}
}

static int	other_try(t_gnl *gnl, char **remainder, char **line)
{
	char	*tmp;

	tmp = ft_strchr(*remainder, '\n');
	if (tmp)
	{
		*tmp++ = '\0';
		*line = ft_strdup(*remainder);
		if (!(*line))
			return (-1);
		*remainder = ft_strcpy(*remainder, tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup(*remainder);
		if (!(*line))
			return (-1);
		free(*remainder);
		*remainder = NULL;
		return (first_try(gnl, remainder, line));
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	t_gnl		gnl;

	gnl.fd = fd;
	gnl.rp = 0;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (remainder)
	{
		*line = NULL;
		return (other_try(&gnl, &remainder, line));
	}
	else
	{
		*line = NULL;
		return (first_try(&gnl, &remainder, line));
	}
}
