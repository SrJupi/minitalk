/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:33 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/03/09 13:15:18 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_status(int counter, int size)
{
	ft_putstr_fd("\rSending chars: ", 1);
	ft_putnbr_fd(counter, 1);
	ft_putchar_fd('/', 1);
	ft_putnbr_fd(size, 1);
}

static int	send_char(int pid, char c)
{
	int	bit;
	int	sig;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
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

static int	handle_str(int pid, char *str)
{
	int	size;
	int	counter;
	int	percent;

	size = ft_strlen(str);
	percent = size / 50;
	if (percent == 0)
		percent = 1;
	counter = 0;
	while (*str)
	{
		if (counter % percent == 0)
			print_status(counter, size);
		if (send_char(pid, *str))
			return (1);
		str++;
		counter++;
	}
	print_status(counter--, size);
	send_char(pid, '\0');
	ft_putstr_fd("\nMessage Sent!\n", 1);
	return (0);
}

static void	handle_sig(int sig)
{
	usleep(100);
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("\nERROR SENDING MESSAGE!\n", 1);
		exit (1);
	}
}

int	check_pid(char *pid_str)
{
	int		pid;
	char	*pid_itoa;

	pid = 0;
	while (pid_str[pid])
	{
		if (!ft_isdigit(pid_str[pid]))
			return (1);
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
	{
		ft_putstr_fd("Error. Client takes two parameters:\n", 1);
		ft_putstr_fd("./client [SERVER_PID] [Message]\n", 1);
		return (1);
	}
	if (check_pid(argv[1]))
	{
		ft_putstr_fd("Error. PID not valid!\n", 1);
		return (1);
	}
	if (argv[2][0] == '\0')
	{
		ft_putstr_fd("Error. Trying to send empty string!\n", 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (check_args(argc, argv))
		return (1);
	ft_putchar_fd('\n', 1);
	if (handle_str(ft_atoi(argv[1]), argv[2]))
	{
		ft_putstr_fd("\nError. Server not found!\n", 1);
		return (1);
	}
	return (0);
}
