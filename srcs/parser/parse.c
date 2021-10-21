#include "minishell.h"

char *str_enlarge(char *orig, char *add)
{
	size_t orig_len;
	size_t add_len;
	char *result;

	orig_len = ft_strlen(orig);
	add_len = ft_strlen(add);
	result = ft_calloc(orig_len + add_len + 1, sizeof(char));
	ft_strlcpy(result, orig, orig_len + 1);
	ft_strlcat(result, add, add_len + orig_len + 1);

	free(orig);
	return (result);
}

t_list **get_commands(t_list **tokens)
{
	t_command *cmd;
	t_list **commands;
	int next_cmd;
	t_redirects cmd_redirs;

	next_cmd = 1;

	commands = malloc(sizeof(t_list *));
	*commands = NULL;
	while(next_cmd)
	{
		cmd = malloc(sizeof(t_command));
		cmd->path = get_path(tokens);
		/* fprintf(stderr, "==> current token = [%s]\n", ((t_word_desc *)((*tokens)->content))->word); */
		cmd->arg = get_args(tokens, cmd->path);
		/* fprintf(stderr, "==> token after args = [%s]\n", ((t_word_desc *)((*tokens)->content))->word); */
		cmd_redirs = get_redir(tokens);
		cmd->red = cmd_redirs.redir;
		cmd->append = cmd_redirs.append;
		if ((*tokens))
		{
			if (!ft_strncmp(((t_word_desc *)(*tokens)->content)->word , "|", 2))
			{
				cmd->pipe = 1;
				*tokens = (*tokens)->next;
			}
			else
				cmd->pipe = 0;
		}
		else
			cmd->pipe = 0;
		ft_lstadd_back(commands, ft_lstnew(cmd));
		next_cmd = cmd->pipe;
	}
	if (DEBUG)
		commands_print(commands);

	return (commands);
}

void	parse(t_minishell *mini)
{
	t_list	**tokens;
	t_list	**commands;
	t_list	*head_token;

	tokens = string_tokenize(mini);
	vars_substitute(tokens, mini);
	if (DEBUG)
	{
		fprintf(stderr, "=== tokens expanded: ===\n");
		word_list_print(tokens);
	}
	head_token = *tokens;
	commands = get_commands(&head_token);
	word_list_free(tokens);
	free(tokens);
	mini->commands = *commands;
	free(commands);
	if (DEBUG)
		fprintf(stderr, "========================================\n");
}
