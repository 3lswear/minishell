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
	fprintf(stderr, ">>>\n");
	fprintf(stderr, "path = [%s]\n", cmd->path);
	fprintf(stderr, "arg = ");
	strarr_print(cmd->arg);
	/* fprintf(stderr, "envp = [%d]", ); */
	/* strarr_print(cmd->envp); */
	fprintf(stderr, "pipe = [%d]\n", cmd->pipe);
	fprintf(stderr, "<<<\n");
	// redirect

}

void	commands_print(t_list **cmds)
{
	t_list *li;

	li = *cmds;
	fprintf(stderr, "=== commands : ===\n");
	while (li)
	{
		cmd_print(li->content);
		li = li->next;
	}
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
	if (!token)
		return (NULL);
	word = token->content;
	if ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
	{
		path = ft_strdup(word->word);
		while ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
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
	}
	
	return (path);
}

static size_t args_count(t_list *arg_tok)
{
	size_t result;
	t_word_desc *word;

	result = 0;
	while(arg_tok)
	{
		word = arg_tok->content;
		/* if current token is special symbol */
		if (word->flags & T_SPEC)
			break;
		else if (word->flags & T_NOSPC)
		{
			if (((t_word_desc *)arg_tok->next->content)->flags & T_SPEC)
			{
				result++;
				break;
			}
		}
		else
			result++;
		/* else */
		/* 	result++; */
		arg_tok = arg_tok->next;
	}

	return (result);
}

char **get_args(t_list **tokens, char *path)
{
	size_t arg_num;
	char **result;
	t_word_desc *word;
	t_list *token;
	size_t i;
	char *tmp;

	token = *tokens;
	arg_num = args_count(*tokens);
	fprintf(stderr, "arg count is [%lu]\n", arg_num);
	result = ft_calloc(sizeof(char *), arg_num + 2);
	result[0] = path;

	//add args to result[x], combining if no space between
	token = *tokens;
	if (!token || ((t_word_desc *)token->content)->flags & T_SPEC)
		return (result);
	i = 1;
	while (i <= arg_num)
	{
		word = token->content;
		if ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
		{
			tmp = ft_strdup(word->word);
			while ((word->flags & T_NOSPC) && token->next && !(((t_word_desc *)token->next->content)->flags & T_SPEC))
			{
				token = token->next;
				word = token->content;
				tmp = str_enlarge(tmp, word->word);
				*tokens = token->next;
			}
		}
		else
		{
			tmp = ft_strdup(word->word);
			*tokens = token->next;
			token = token->next;
		}
		result[i] = tmp;
		i++;
	}

	return (result);
}

t_list **get_commands(t_list **tokens)
{
	t_command *cmd;
	t_list **commands;
	int next_cmd;

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
		if ((*tokens))
		{
			if (ft_strncmp(((t_word_desc *)*tokens)->word , "|", 2))
			{
				cmd->pipe = 1;
				*tokens = (*tokens)->next;
			}
		}
		else
			cmd->pipe = 0;
		cmd->red = NULL;
		cmd->append = NULL;
		ft_lstadd_back(commands, ft_lstnew(cmd));
		next_cmd = cmd->pipe;
	}
	commands_print(commands);

	return (commands);
}

void	parse(t_minishell *mini)
{
	t_list	**tokens;
	t_list	**commands;
	t_list	*head_token;

	tokens = string_tokenize(mini);
	handle_assignment(tokens);
	head_token = *tokens;
	commands = get_commands(&head_token);
	/* word_list_print(tokens); */
	word_list_free(tokens);
	free(tokens);
	mini->commands = *commands;
	free(commands);
}
