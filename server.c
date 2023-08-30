/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:22 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/30 17:57:32 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	restart_server(t_str *my_str)
{
	ft_putstr_fd("\nError found! Restarting server...\n", 2);
	usleep(1000);
	kill(my_str->pid, SIGUSR2);
	clean_str(my_str);
}

static void	set_pid(t_str *my_str, int pid)
{
	if (pid <= 0)
		return ;
	my_str->pid = pid;
	kill(pid, SIGUSR1);
}

static void	handler_usr(int signal, siginfo_t *info, void *context)
{
	static t_str	my_str;

	(void)context;
	usleep(200);
	if (!my_str.pid)
		return (set_pid(&my_str, info->si_pid));
	else if (my_str.pid != info->si_pid)
		return ;
	else if (my_str.m_alloc == 0)
	{
		if (receive_size(signal, &my_str))
			return (restart_server(&my_str));
	}
	else if (my_str.check == 0)
		receive_check(signal, &my_str);
	else
	{
		if (receive_char(signal, &my_str))
			return (restart_server(&my_str));
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler_usr;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		;
	return (0);
}
