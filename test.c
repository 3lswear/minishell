#include <stdio.h>

int main()
{
	char	*b = "boba=bibabulino";
	int	i = 4;
	int	len = 15;
	printf("%s\n",(char *) *b - (len - i));
	return (0);
}
