/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:22 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/04/12 11:34:18 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*static void	block_signals(void)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	sigprocmask(SIG_BLOCK, &sigset, NULL);
}

static void	unblock_signals(void)
{
	sigset_t	sigset;

	sigfillset(&sigset);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
}*/

static void	restart_server(t_str *my_str)
{
	ft_putstr_fd("\nError found! Restarting server...\n", 2);
	usleep(1000);
	kill(my_str->pid, SIGUSR2);
	clean_str(my_str);
//	unblock_signals();
}

static void	set_pid(t_str *my_str, int pid)
{
	my_str->pid = pid;
	kill(pid, SIGUSR1);
}

static void	handler_usr(int signal, siginfo_t *info, void *context)
{
	static t_str	my_str;

	(void)context;
//	block_signals();
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
//	unblock_signals();
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
	{
		pause();
	}
	return (0);
}
