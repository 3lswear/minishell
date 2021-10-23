#include "minishell.h"

void	handle_dollar(char *str, int *i, t_list *tokens)
{
	char	*delim;
	int		len;
	int		flags;

	delim = " \t\n$><|";
	if (str[*i] != '$')
		return ;
	(*i)++;
	len = 0;
	flags = 0;
	while (str[*i + len] && in_set(&str[*i + len], delim))
	{
		len++;
	}
	if (!in_set(&str[*i + len + 1], " \t\n"))
		flags |= T_NOSPC;
	ft_lstadd_back(&tokens, ft_lstnew(wdesc_new(ft_substr(str, *i, len),
				T_NOEXP | T_VAR)));
}

int	handle_dquote(char *str, int *i, t_list **tokens, int flag_add)
{
	int	len;

	if (str[*i] != 0x22)
		return (0);
	/* if ((*i) && str[*i - 1] == '\\') */
	/* 	return (0); */
	(*i)++;
	len = ft_strchr(&str[*i], 0x22) - &str[*i];
	if (len < 0)
	{
		handle_error(ERR_P_MISSING, "closing \'\"\'");
		word_list_free(tokens);
		str[*i] = 0;
		return (ERR_P_MISSING);
	}
	if (!in_set(&str[*i + len + 1], " \t\n"))
		flag_add |= T_NOSPC;
	word_li_append(tokens, ft_substr(str, *i, len), T_DQUOTE | flag_add);
	*i += len + 1;
	return (0);
}

int	handle_quote(char *str, int *i, t_list **tokens, int flag_add)
{
	int	len;

	if (str[*i] != 0x27)
		return (0);
	/* if ((*i) && str[*i - 1] == '\\') */
	/* 	return (0); */
	(*i)++;
	len = ft_strchr(&str[*i], 0x27) - &str[*i];
	if (len < 0)
	{
		handle_error(ERR_P_MISSING, "closing \'\'\'");
		word_list_free(tokens);
		str[*i] = 0;
		return (ERR_P_MISSING);
	}
	if (!in_set(&str[*i + len + 1], " \t\n"))
		flag_add |= T_NOSPC;
	word_li_append(tokens, ft_substr(str, *i, len), T_NOEXP | flag_add);
	*i += len + 1;
	return (0);
}
