#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <termio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// ╰─ sudo apt-get install libreadline8 libreadline-dev  установить readline.

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

void	read_line(char **env);

#endif