/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:33 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/16 12:27:32 by lsulzbac         ###   ########.fr       */
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

static void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
		{
			kill(pid, SIGUSR1);
			pause();
		}
		else
		{
			kill(pid, SIGUSR2);
			pause();
		}
		bit++;
	}
}

static void	handle_str(int pid, char *str)
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
		send_char(pid, *str);
		str++;
		counter++;
	}
	print_status(counter--, size);
	send_char(pid, '\0');
	ft_putstr_fd("\nMessage Sent!\n", 1);
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

int	main(int argc, char **argv)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = &handle_sig;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	if (argc != 3)
	{
		ft_putstr_fd("Error. Client takes two parameters:\n", 1);
		ft_putstr_fd("./client [SERVER_PID] [Message]\n", 1);
	}
	else
	{
		ft_putchar_fd('\n', 1);
		handle_str(ft_atoi(argv[1]), argv[2]);
	}
	return (0);
}
