#include "minishell.h"

static int	print_err(int code, char *msg, char *token)
{
	ft_putstr_fd("minishell: 😨 syntax error: ", 2);
	if (code == ERR_P_UNEXP)
	{
		ft_putstr_fd("unexpected token: \"", 2);
		ft_putstr_fd(token, 2);
	}
	else if (code == ERR_P_MISSING)
	{
		ft_putstr_fd(msg, 2);
		ft_putendl_fd(token, 2);
	}
	else
	{
		ft_putendl_fd(msg, 2);
	}
	/* exit(code); */
	return (code);
}

void	handle_error(int code, char *token)
{
	char *msg;

	if (code == ERR_P_SYNTAX)
		msg = "Syntax error.";
	else if (code == ERR_P_MISSING)
		msg = "missing ";
	else
		msg = "Unknown errOR 🤔";
	print_err(code, msg, token);
}
