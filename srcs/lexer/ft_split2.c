#include "minishell.h"

/* split string by delim, creating list of tokens,
 * adding flags to each and special_flg to a token with delim as a word */
t_list	**ft_split2(char const *s, const char *delim, int flags,
		int special_flg)
{
	int		len;
	int		delim_len;
	char	*substr;
	t_list	**list;

	list = malloc(sizeof(t_list *));
	*list = NULL;
	len = ft_strlen(s);
	delim_len = ft_strlen(delim);
	substr = ft_strnstr(s, delim, len);
	if (!substr)
	{
		free(list);
		return (NULL);
	}
	while (s)
	{
		substr = ft_strnstr(s, delim, len);
		if (substr)
		{
			/* if s contains ONLY delim */
			if (len == delim_len)
				ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(substr, 0, delim_len), flags | special_flg)));
			/* if there is a string BEFORE the delim */
			else
			{
				if (substr - s)
					ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(s, 0, substr - s), flags | T_NOSPC)));
				ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(substr, 0, delim_len), flags | T_NOSPC | special_flg)));
			}
			s = substr + delim_len;
		}
		else
		{
			if (*s)
				ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(s, 0, len), flags)));
			break ;
		}
	}
	return (list);
}
