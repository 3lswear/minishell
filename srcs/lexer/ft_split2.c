#include "minishell.h"

static int	loop(t_split *sp, t_list **list, int flags, int special_flg)
{
	if (sp->substr)
	{
		if (sp->len == sp->delim_len)
			ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(sp->substr,
							0, sp->delim_len), flags | special_flg)));
		else
		{
			if (sp->substr - sp->str)
				ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(sp->str, 0,
								sp->substr - sp->str), flags | T_NOSPC)));
			ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(sp->substr,
							0, sp->delim_len), flags | T_NOSPC | special_flg)));
		}
		sp->str = sp->substr + sp->delim_len;
		return (0);
	}
	else
	{
		if (*sp->str)
			ft_lstadd_back(list, ft_lstnew(wdesc_new(ft_substr(sp->str,
							0, sp->len), flags)));
		return (1);
	}
}

/* split string by delim, creating list of tokens,
 * adding flags to each and special_flg to a token with delim as a word */
t_list	**ft_split2(const char *s, const char *delim, int flags,
		int special_flg)
{
	t_list	**list;
	t_split	sp;

	list = ft_calloc(sizeof(t_list *), 1);
	ft_bzero(&sp, sizeof(t_split));
	sp.str = s;
	sp.len = ft_strlen(s);
	sp.delim = delim;
	sp.delim_len = ft_strlen(delim);
	sp.substr = ft_strnstr(s, delim, sp.len);
	if (!sp.substr)
	{
		free(list);
		return (NULL);
	}
	while (*sp.str)
	{
		sp.substr = ft_strnstr(sp.str, delim, sp.len);
		if (loop(&sp, list, flags, special_flg))
			break ;
	}
	return (list);
}
