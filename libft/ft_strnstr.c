/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:11:45 by talyx             #+#    #+#             */
/*   Updated: 2021/08/15 18:11:45 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*my_big;
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	my_big = (char *)big;
	i = 0;
	if (!little_len)
		return (my_big);
	if (ft_strlen(big) < little_len || len < little_len)
		return (NULL);
	while (my_big[i] && i <= len - little_len)
	{
		j = 0;
		while (little[j] && little[j] == my_big[i + j])
			j++;
		if (j == little_len)
			return (&my_big[i]);
		i++;
	}
	return (NULL);
}
