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
	if (cmd->red)
	{
		fprintf(stderr, " > to [%s]\n", cmd->red->out);
		fprintf(stderr, " < from [%s]\n", cmd->red->in);
	}
	else
		fprintf(stderr, "- redirects\n");
	if (cmd->append)
	{
		fprintf(stderr, " >> to [%s]\n", cmd->append->out);
		fprintf(stderr, " << from [%s]\n", cmd->append->in);
	}
	else
		fprintf(stderr, "- no appends\n");
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
