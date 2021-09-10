/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talyx <talyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 21:08:17 by talyx             #+#    #+#             */
/*   Updated: 2021/09/10 11:43:04 by talyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(char **env)
{
	char	*buff;

	buff = "";
	while (!ft_strequ(buff, "exit"))
	{
		buff = readline("minishell➢ ");
		if(ft_strlen(buff) > 0)
			add_history(buff);		
	}
	(void)env;
}

// void	read_line(char **env)
// {
// 	char str[50];
// 	int l;
// 	struct termios term;
// 	tcgetattr(0, &term);
// 	term.c_lflag &= ~(ECHO);
// 	term.c_lflag &= ~(ICANON);
// 	tcsetattr(0, TCSANOW, &term);
// 	str[0] = '0';
// 	while (!ft_strequ(str, "exit\n"))
// 	{
// 		ft_putstr("minishell➢ ");
// 		ft_memset(str, 0, ft_strlen(str));
// 		while (!ft_strequ(str, "\n"))
// 		{
// 			l = read(0, str, 60);
// 			write(1, str, l);
// 		}
// 	}
// 	(void)env;
// }

// void	read_line(char **env)
// {
// 	char	*line;

// 	line = "none";
// 	while (!ft_strequ(line, "exit"))
// 	{
// 		ft_putstr("minishell➢ ");
// 		// ft_memset(line, 0, ft_strlen(line));
// 		get_next_line(0, &line);
// 		// write(1, line, ft_strlen(line));
// 		// write(1, "\n", 1);
// 	}
// 	(void)env;
// }