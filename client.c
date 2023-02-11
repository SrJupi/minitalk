/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:33 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/09 13:15:47 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int pid, char c)
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

void	handle_str(int pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

void	handle_sig(int sig)
{
	(void)sig;
	usleep(200);
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("ERROR ON SERVER!\n", 1);
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
