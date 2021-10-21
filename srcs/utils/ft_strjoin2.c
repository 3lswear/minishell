#include "minishell.h"

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free((char *)s1);
	return (result);
}
