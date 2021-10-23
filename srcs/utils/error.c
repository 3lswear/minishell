/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:12:20 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/23 20:12:27 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_err(int code, char *msg, char *token)
{
	ft_putstr_fd("minishell: syntax error 😨: ", 2);
	if (code == ERR_P_UNEXP)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd("\"", 2);
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
	return (code);
}

void	handle_error(int code, char *token)
{
	char	*prefix;

	if (code == ERR_P_SYNTAX)
		prefix = "syntax error.";
	else if (code == ERR_P_MISSING)
		prefix = "missing ";
	else if (code == ERR_P_UNEXP)
		prefix = "unexpected token: \"";
	else
		prefix = "unknown error 🤔";
	print_err(code, prefix, token);
}
