#ifndef ERROR_H
# define ERROR_H
#include "minishell.h"

#define ERR_P_SYNTAX	100
#define ERR_P_VAR		101
#define ERR_P_UNEXP		102
#define ERR_P_MISSING	103
#define ERR_P_NOCMD		104
#define ERR_P_NOREDOUT	105
#define ERR_P_NOREDIN	106

void	handle_error(int code, char *token);
int		ft_error_export(char *arg, int error);
#endif

