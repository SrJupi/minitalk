/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:33 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/07 11:25:31 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_str(int pid, char *str)
{
	int	bit;

	while (*str)
	{
		bit = 0;
		while (bit < 8)
		{
			if (*str & (1 << bit))
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
		ft_putchar_fd(*str, 1);
		str++;
	}
/*	while (bit > 0)
	{
		bit--;
		kill(pid, SIGUSR2);
		pause();
	}*/
}

void	handle_sig(int sig)
{
	(void)sig;
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
