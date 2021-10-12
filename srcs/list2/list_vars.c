#include "minishell.h"

t_list_vars *list_vars_new(char *name, char *value)
{
	t_list_vars *result;

	result = malloc(sizeof(t_list_vars));
	if (!result)
		return (NULL);
	result->var.name = name;
	result->var.value = value;
	((t_list_head *)result)->next = NULL;
	return (result);
}
