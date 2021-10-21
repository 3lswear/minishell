#include "minishell.h"

void	redir_error_dup(char *redir_op, t_minishell *mini)
{
	if (redir_op)
	{
		handle_error(ERR_P_UNEXP, redir_op);
		mini->exit_status = ERR_P_UNEXP;
	}
}

char	*dispatch_to_redir_field(t_redirects *res, char *redir_op,
		char *filename)
{
		if (!ft_strncmp(redir_op, ">", 2))
			if (!res->redir->out)
				res->redir->out = filename;
			else
				return (">");
		else if (!ft_strncmp(redir_op, "<", 2))
			if (!res->redir->in)
				res->redir->in = filename;
			else
				return ("<");
		else if (!ft_strncmp(redir_op, ">>", 2))
			if (!res->append->out)
				res->append->out = filename;
			else
				return (">>");
		else if (!ft_strncmp(redir_op, "<<", 2))
		{
			if (!res->append->in)
				res->append->in = filename;
			else
				return ("<<");
		}
		return (NULL);
}

t_redirects get_redir(t_list **tokens, t_minishell *mini)
{
	t_redirects res;
	t_list *token;
	t_word_desc *word;
	char *filename;
	char *redir_op;

	token = *tokens;
	res.append = ft_calloc(sizeof(t_redir), 1);
	res.redir = ft_calloc(sizeof(t_redir), 1);
	if (!token)
		return (res);
	word = token->content;
	while (*tokens && (word->flags & T_REDIR) && (!(res.redir->in) ||
				!(res.redir->out) || !(res.append->in) || !(res.append->out)))
	{
		word = (*tokens)->content;
		redir_op = word->word;
		*tokens = (*tokens)->next;
		filename = tokens_merge(tokens, 0);
		if (!filename || !(*filename))
		{
			handle_error(ERR_P_MISSING, "redirect argument");
			mini->exit_status = ERR_P_MISSING;
		}
		redir_error_dup(dispatch_to_redir_field(&res, redir_op, filename),
				mini);
		if (mini->exit_status)
			break;
	}
	return (res);
}
