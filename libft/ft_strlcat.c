/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:11:45 by talyx             #+#    #+#             */
/*   Updated: 2021/08/15 18:11:45 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	free_space;
	size_t	dst_length;
	size_t	result_size;
	size_t	i;

	i = 0;
	dst_length = ft_strlen(dst);
	if (dst_length < size)
		result_size = dst_length + ft_strlen(src);
	else
		result_size = size + ft_strlen(src);
	free_space = size - dst_length;
	if (dst_length < size)
	{
		while (src[i] != '\0' && free_space > 1)
		{
			dst[dst_length++] = *src++;
			free_space--;
		}
		dst[dst_length] = '\0';
	}
	return (result_size);
}
