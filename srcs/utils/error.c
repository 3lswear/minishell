#include "minishell.h"

static int	print_err(int code, char *msg)
{
	ft_putstr_fd("minishell: 😨 error:", 2);
	ft_putendl_fd(msg, 2);
	exit(code);
}

void	handle_error(int code)
{
	char *msg;

	if (code == ERR_P_SYNTAX)
		msg = "Syntax error.";
	else
		msg = "Unkown errOR 🤔";
	print_err(code, msg);
}
