/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:07:08 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/24 19:48:38 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_error_dup(char *redir_op, t_minishell *mini)
{
	if (redir_op)
	{
		handle_error(ERR_P_UNEXP, redir_op);
		mini->parse_status = ERR_P_UNEXP;
	}
}

int	redir_error_missing(char *filename, t_minishell *mini)
{
	if (!filename || !(*filename))
	{
		handle_error(ERR_P_MISSING, "redirect argument");
		mini->parse_status = ERR_P_MISSING;
		return (1);
	}
	else
		return (0);
}
