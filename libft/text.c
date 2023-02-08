#include <stdio.h>

int checksum(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ret ^= str[i];
		i++;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	(void)argc;
	printf("%i", checksum(argv[1]));
}
