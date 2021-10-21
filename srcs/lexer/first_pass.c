#include "minishell.h"

int		in_set(char *chr, const char *special)
{
	char *special_copy;

	special_copy = (char *)special;
	while (*special_copy)
	{
		if (*chr == *special_copy)
			return (1);
		else
			special_copy++;
	}
	return (0);
}

void	handle_dollar(char *str, int *i, t_list *tokens)
{
	char *delim;
	int len;
	int flags;

	delim = " \t\n$><|";
	if (str[*i] != '$')
		return;
	(*i)++;
	len = 0;
	flags = 0;
	while (str[*i + len] && in_set(&str[*i + len], delim))
	{
		len++;
	}
	if (!in_set(&str[*i + len + 1], " \t\n"))
		flags |= T_NOSPC;
	ft_lstadd_back(&tokens, ft_lstnew(wdesc_new(ft_substr(str, *i, len), T_NOEXP | T_VAR)));

}

int	handle_dquote(char *str, int *i, t_list **tokens, int flag_add)
{
	int len;

	if (str[*i] != 0x22)
		return (0);
	if ((*i) && str[*i - 1] == '\\')
		return (0);
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
	int len;

	if (str[*i] != 0x27)
		return (0);
	if ((*i) && str[*i - 1] == '\\')
		return (0);
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

int		is_sep(char *chr)
{
	return (*chr == '|' || *chr == ' ' || *chr == '>' || *chr == '<');
}

void	scroll_ifs(char *str, int *i)
{
	if (!str || !(*str))
		return;
	while ((str[*i] == ' ') || (str[*i] == '\n') || (str[*i] == '\t'))
	{
		(*i)++;
	}
}

static int	loop(int *i, char *str, t_list **tokens, int add)
{
	int	j;
	int	error;

	error = 0;
	j = *i;
	while (str[j] && !in_set(&str[j], IFS) && str[j] != '\''
		&& str[j] != '\"')
		j++;
	if (str[j] == '\'')
	{
		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add);
		error |= handle_quote(str, &j, tokens, 0);
	}
	else if (str[j] == '\"')
	{
		word_li_append(tokens, ft_substr(str, *i, j - *i), T_NOSPC | add);
		error |= handle_dquote(str, &j, tokens, 0);
	}
	else
		word_li_append(tokens, ft_substr(str, *i, j - *i), add);
	*i = j;
	return (error);
}

// splits by IFS, respecting quotes
t_list	**first_pass(char *str, t_minishell *mini, int add)
{
	t_list	**tokens;
	int		i;
	int		error;

	tokens = ft_calloc(sizeof(t_list *), 1);
	i = 0;
	error = 0;
	while (str[i])
	{
		scroll_ifs(str, &i);
		while (str[i] && !error)
		{
			scroll_ifs(str, &i);
			error |= handle_quote(str, &i, tokens, add);
			error |= handle_dquote(str, &i, tokens, add);
			scroll_ifs(str, &i);
			if (!str[i])
				break ;
			error = loop(&i, str, tokens, add);
			scroll_ifs(str, &i);
		}
		if (error)
			mini->exit_status = error;
	}
	return (tokens);
}
