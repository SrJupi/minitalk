#include "minitalk.h"

int	param_error(void)
{
	ft_putstr_fd("Error. Client takes two parameters:\n", 2);
	ft_putstr_fd("./client [SERVER_PID] [Message]\n", 2);
	return (1);
}

int	pid_error(void)
{
	ft_putstr_fd("Error. PID not valid!\n", 2);
	return (1);
}

int	empty_str_error(void)
{
	ft_putstr_fd("Error. Trying to send empty string!\n", 2);
	return (1);
}

int	not_server_error(void)
{
	ft_putstr_fd("Error. Server not found!\n", 2);
	return (1);
}
