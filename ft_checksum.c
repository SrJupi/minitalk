#include "minitalk.h"

char	ft_checksum(char *str)
{
	char	check;

	check = 0;
	while (*str)
	{
		check ^= *str;
		str++;
	}
	return (check);
}
