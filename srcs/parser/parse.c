#include "minishell.h"

void	strarr_print(char **arr)
{
	int i;

	i = 0;
	/* fprintf(stderr, ">>>\n"); */
	while(arr[i])
	{
		fprintf(stderr, "[%s], ", arr[i]);
		i++;
	}
	/* fprintf(stderr, "<<<\n"); */
	fprintf(stderr, "\n");

}

void	cmd_print(t_command *cmd)
{
	fprintf(stderr, "path = [%s]\n", cmd->path);
	fprintf(stderr, "arg = ");
	strarr_print(cmd->arg);
	fprintf(stderr, "envp = ");
	/* strarr_print(cmd->envp); */
	fprintf(stderr, "pipe = [%d]\n", cmd->pipe);
	// redirect

}

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

char	*get_path(t_list **tokens)
{
	char		*path;
	t_list		*token;
	t_word_desc	*word;

	token = *tokens;
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next)
	{
		path = ft_strdup(word->word);
		while ((word->flags & T_NOSPC) && token->next)
		{
			token = token->next;
			word = token->content;
			path = str_enlarge(path, word->word);
			*tokens = token->next;
		}
	}
	else
	{
		path = ft_strdup(word->word);
		*tokens = token->next;
		/* word_li_free(token); */
	}
	
	return (path);
}

t_list **get_commands(t_list **tokens)
{
	t_command *cmd;
	t_list **commands;
	int pipe;
	/* (void) tokens; */

	pipe = 1;

	/* fprintf(stderr, "%s\n", str_enlarge("hello ", "world")); */
	while(pipe)
	{
		cmd = malloc(sizeof(t_command));
		/* cmd->path = "imposter"; */
		cmd->path = get_path(tokens);
		fprintf(stderr, "==> current token = [%s]\n", ((t_word_desc *)((*tokens)->content))->word);
		cmd->arg = ft_calloc(sizeof(char *), 100); //TODO
		cmd->arg[0] = cmd->path;
		cmd->arg[1] = NULL;
		/* cmd->envp = NULL; */
		/* cmd->option = NULL; */
		cmd->pipe = 0;
		cmd->red = NULL;
		cmd->append = NULL;
		commands = malloc(sizeof(t_list *));
		*commands = NULL;
		ft_lstadd_back(commands, ft_lstnew(cmd));
		pipe = cmd->pipe;
	}

	return (commands);
}

void	parse(t_minishell *mini)
{
	t_list **tokens;
	t_list **commands;

	tokens = string_tokenize(mini);
	commands = get_commands(tokens);
	mini->commands = *commands;

}
