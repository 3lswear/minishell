#include "minishell.h"

char	*str_enlarge(char *orig, char *add)
{
	size_t	orig_len;
	size_t	add_len;
	char	*result;

	orig_len = ft_strlen(orig);
	add_len = ft_strlen(add);
	result = ft_calloc(orig_len + add_len + 1, sizeof(char));
	ft_strlcpy(result, orig, orig_len + 1);
	ft_strlcat(result, add, add_len + orig_len + 1);
	free(orig);
	return (result);
}

t_list	*get_commands(t_list **tokens, t_minishell *mini)
{
	t_command	*cmd;
	t_list		*commands;
	int			next_cmd;
	t_redirects	cmd_redirs;

	next_cmd = 1;
	/* commands = malloc(sizeof(t_list *)); */
	commands = NULL;
	while (next_cmd && !(mini->exit_status))
	{
		cmd = malloc(sizeof(t_command));
		cmd_redirs = get_redir(*tokens, mini);
		cmd->red = cmd_redirs.redir;
		cmd->append = cmd_redirs.append;
		cmd->path = get_path(tokens);
		cmd->arg = get_args(tokens, cmd->path);
		cmd->pipe = get_pipe(tokens, mini);
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		next_cmd = cmd->pipe;
	}
	if (!mini->exit_status)
		validity_check(&commands, mini);
	if (DEBUG)
		commands_print(&commands);
	return (commands);
}

int	parse(t_minishell *mini)
{
	t_list	**tokens;
	t_list	*head_token;
	int		parser_status;
	int		saved_exit;

	parser_status = 0;
	saved_exit = mini->exit_status;
	tokens = string_tokenize(mini);
	if ((saved_exit != mini->exit_status) && mini->exit_status)
	{
		parser_status = mini->exit_status;
		saved_exit = mini->exit_status;
	}
	vars_substitute(tokens, mini);
	if (DEBUG)
	{
		fprintf(stderr, "=== tokens expanded: ===\n");
		word_list_print(tokens);
	}
	head_token = *tokens;
	mini->commands = get_commands(&head_token, mini);
	if ((saved_exit != mini->exit_status) && mini->exit_status)
		parser_status = mini->exit_status;
	if (!mini->exit_status && parser_status)
		mini->exit_status = parser_status;
	word_list_free(tokens);
	free(tokens);
	if (DEBUG)
		fprintf(stderr, "========================================\n");
	return (parser_status);
}
