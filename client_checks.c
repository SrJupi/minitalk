#include "minitalk.h"

int	check_pid(char *pid_str)
{
	int		pid;
	char	*pid_itoa;

	pid = 0;
	while (pid_str[pid])
	{
		if (!ft_isdigit(pid_str[pid]))
			return (1);
		pid++;
	}
	pid = ft_atoi(pid_str);
	if (pid <= 0)
		return (1);
	pid_itoa = ft_itoa(pid);
	if (pid_itoa == NULL)
		return (1);
	if (ft_strncmp(pid_str, pid_itoa, ft_strlen(pid_str)))
	{
		free(pid_itoa);
		return (1);
	}
	free(pid_itoa);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 3)
		return (param_error());
	if (check_pid(argv[1]))
		return (pid_error());
	if (argv[2][0] == '\0')
		return (empty_str_error());
	return (0);
}

int	check_server(int pid)
{
	if (kill(pid, SIGUSR1) == -1)
		return (1);
	usleep(500);
	return (0);
}
