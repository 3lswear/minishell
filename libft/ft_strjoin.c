/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:11:45 by talyx             #+#    #+#             */
/*   Updated: 2021/08/15 18:11:45 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*megazord;
	int		len;
	int		i;
	int		j;

	if (!s1)
		return (0);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	megazord = (char *)malloc(sizeof(char) * (len + 1));
	if (!megazord)
		return (NULL);
	while (s1[i])
	{
		megazord[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		megazord[i + j] = s2[j];
		j++;
	}
	megazord[i + j] = '\0';
	return (megazord);
}
