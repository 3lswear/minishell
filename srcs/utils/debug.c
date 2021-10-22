#include "minishell.h"

void	string_list_print(t_list **list, char *prefix)
{
	t_list *li;

	li = *list;
	if (!prefix)
		prefix = "";
	if (!li)
		return;
	while (li)
	{
		fprintf(stderr, "%s [%s], ", prefix, (char *)li->content);
		li = li->next;
	}
	fprintf(stderr, "\n");
}

void	split_print(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		fprintf(stderr, "(%s), ", split[i++]);
	}
	fprintf(stderr, "\n");
}

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
		string_list_print(&cmd->red->out, ">");
		string_list_print(&cmd->red->in, "<");
	}
	else
		fprintf(stderr, "- redirects\n");
	if (cmd->append)
	{
		string_list_print(&cmd->append->in, "<<");
		string_list_print(&cmd->append->out, ">>");
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

char *get_flag_name(int flag)
{
	char *result;

	result = ft_calloc(sizeof(char), 1);
	if (flag & T_NOEXP)
		result = ft_strjoin2(result, "T_NOEXP ");
	if (flag & T_DQUOTE)
		result = ft_strjoin2(result, "T_DQUOTE ");
	if (flag & T_NOSPC)
		result = ft_strjoin2(result, "T_NOSPC ");
	if (flag & T_ASSIGN)
		result = ft_strjoin2(result, "T_ASSIGN ");
	if (flag & T_SPEC)
		result = ft_strjoin2(result, "T_SPEC ");
	if (flag & T_VAR)
		result = ft_strjoin2(result, "T_VAR ");
	if (flag & T_REDIR)
		result = ft_strjoin2(result, "T_REDIR ");

	return (result);
}

void	word_list_print(t_list **head)
{
	t_list	*item;
	t_word_desc *word;
	char *str_flag;

	fprintf(stderr, ">>>\n");
	if (!head || !(*head))
	{
		fprintf(stderr, "NULL word list\n");
		return;
	}
	item = *head;
	while (item)
	{
		word = item->content;
		str_flag = get_flag_name(word->flags);
		fprintf(stderr, "[%s],\t\t[%s]\n", word->word, str_flag);
		free(str_flag);
		item = item->next;
	}
	/* fprintf(stderr, "<<END\n"); */
	fprintf(stderr, "<<<\n");
	/* printf("\n"); */
}
