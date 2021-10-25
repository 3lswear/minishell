/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunderle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:10:03 by sunderle          #+#    #+#             */
/*   Updated: 2021/10/25 14:24:53 by sunderle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	validity_check(t_list **cmds_list, t_minishell *mini)
{
	t_command	*cmd;
	t_list		*li;

	li = *cmds_list;
	if (!li)
		return ;
	while (li)
	{
		cmd = li->content;
		if (!(cmd->path) && (!(cmd->red->in) && !(cmd->red->out)
				&& !(cmd->append->in) && !(cmd->append->out)) && cmd->pipe)
		{
			handle_error(ERR_P_UNEXP, "|");
			mini->parse_status = 2;
		}
		if (mini->parse_status)
			break ;
		li = li->next;
	}
}
