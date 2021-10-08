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
	strarr_print(cmd->envp);
	fprintf(stderr, "pipe = [%d]\n", cmd->pipe);
	// redirect

}

t_list **get_commands(t_list **tokens)
{
	t_command *cmd;
	t_list **commands;
	(void) tokens;

	cmd = malloc(sizeof(t_command));
	cmd->path = "ls";
	cmd->arg = ft_calloc(sizeof(char *), 100); //TODO
	cmd->arg[0] = "-la";
	cmd->envp = NULL;
	cmd->option = NULL;
	cmd->pipe = 0;
	cmd->red = NULL;
	cmd->append = NULL;
	commands = malloc(sizeof(t_list *));
	*commands = NULL;
	ft_lstadd_back(commands, ft_lstnew(cmd));

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
