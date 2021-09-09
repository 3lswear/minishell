#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
#include <termio.h>

typedef struct s_env
{
	struct s_env	*prew;
	struct s_env	*next;
	char			*value;
}				t_env;

typedef struct s_minishell
{
	t_env	*env;
	
}				t_minishell;

void	read_line(int argc, char *argv[], char **env);

#endif