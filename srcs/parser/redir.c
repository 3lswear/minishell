#include "minishell.h"

void	redir_error_dup(char *redir_op, t_minishell *mini)
{
	if (redir_op)
	{
		handle_error(ERR_P_UNEXP, redir_op);
		mini->exit_status = ERR_P_UNEXP;
	}
}

static int	redir_error_missing(char *filename, t_minishell *mini)
{
	if (!filename || !(*filename))
	{
		handle_error(ERR_P_MISSING, "redirect argument");
		mini->exit_status = ERR_P_MISSING;
		return (1);
	}
	else
		return (0);
}

int	assign_file_to_op(t_list **redir_field, char *filename)
{
	if (redir_field)
	{
		ft_lstadd_back(redir_field, ft_lstnew(ft_strdup(filename)));
		/* *redir_field = filename; */
		return (0);
	}
	else
		return (1);
}

char	*dispatch_to_redir_field(t_redirects *res, char *redir_op,
		char *filename)
{
	t_list	**redir_field;

	redir_field = NULL;
	if (!ft_strncmp(redir_op, ">", 2))
		redir_field = &(res->redir->out);
	else if (!ft_strncmp(redir_op, "<", 2))
		redir_field = &(res->redir->in);
	else if (!ft_strncmp(redir_op, ">>", 3))
		redir_field = &(res->append->out);
	else if (!ft_strncmp(redir_op, "<<", 3))
		redir_field = &(res->append->in);
	if (assign_file_to_op(redir_field, filename))
		return (redir_op);
	return (NULL);
}

t_redirects	get_redir(t_list **tokens, t_minishell *mini)
{
	t_redirects	res;
	t_word_desc	*word;
	char		*filename;
	char		*op;

	res.append = ft_calloc(sizeof(t_redir), 1);
	res.redir = ft_calloc(sizeof(t_redir), 1);
	if (!tokens || !(*tokens))
		return (res);
	word = (*tokens)->content;
	while (*tokens && (word->flags & T_REDIR))
	{
		op = word->word;
		*tokens = (*tokens)->next;
		filename = tokens_merge(tokens, 0);
		if (!redir_error_missing(filename, mini))
			dispatch_to_redir_field(&res, op, filename);
		free(filename);
		if (mini->exit_status)
			break ;
		if (*tokens)
			word = (*tokens)->content;
	}
	return (res);
}
