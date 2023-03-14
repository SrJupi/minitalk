#include "minitalk.h"

static void	print_status(size_t counter, size_t size)
{
	ft_putstr_fd("\rSending chars: ", 1);
	ft_putnbr_fd(counter, 1);
	ft_putchar_fd('/', 1);
	ft_putnbr_fd(size, 1);
}

static int	send_size(int pid, size_t size)
{
	size_t	bit;
	int		sig;

	bit = 0;
	while (bit < (sizeof(size) * 8))
	{
		if ((size >> bit) & 1)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
			return (1);
		pause();
		bit++;
	}
	return (0);
}

static int	send_char(int pid, char c)
{
	size_t	bit;
	int		sig;

	bit = 0;
	while (bit < (sizeof(c) * 8))
	{
		if ((c >> bit) & 1)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) == -1)
			return (1);
		pause();
		bit++;
	}
	return (0);
}

int	handle_str(int pid, char *str)
{
	size_t	size;
	size_t	counter;

	size = ft_strlen(str);
	if (send_size(pid, size))
		return (1);
	if (send_char(pid, ft_checksum(str)))
		return (1);
	counter = 0;
	while (*str)
	{
		if (counter % ((size / 50) + 1) == 0)
			print_status(counter, size);
		if (send_char(pid, *str))
			return (1);
		str++;
		counter++;
	}
	print_status(counter--, size);
	if (send_char(pid, '\0'))
		return (1);
	ft_putstr_fd("\nMessage Sent!\n", 1);
	return (0);
}