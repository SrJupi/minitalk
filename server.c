/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:22 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/03/09 13:15:14 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	restart_server(int other_pid, t_str *my_str, int *bit, char *c)
{
	ft_putstr_fd("\nError found! Restarting server...\n", 2);
	if (my_str->str != NULL)
		clean_str(&my_str->str);
	usleep(1000);
	if (other_pid)
		kill(other_pid, SIGUSR2);
	kill(my_str->pid, SIGUSR2);
	my_str->m_alloc = 0;
	my_str->i = 0;
	my_str->pid = 0;
	*bit = 0;
	*c = 0;
}

static int	handle_char(char c, t_str *my_str)
{
	if (c)
	{
		if (add_char(c, my_str))
			return (1);
	}
	else
	{
		if (print_str(my_str))
			return (1);
	}
	return (0);
}

static void	set_pid(t_str *my_str, int pid)
{
	my_str->pid = pid;
	kill(pid, SIGUSR1);
}

static void	handler_usr(int signal, siginfo_t *info, void *context)
{
	static int		bit;
	static char		c;
	static t_str	my_str;

	(void)context;
	usleep(50);
	if (!my_str.pid)
		return (set_pid(&my_str, info->si_pid));
	if (my_str.pid != info->si_pid)
		return (restart_server(info->si_pid, &my_str, &bit, &c));
	if (signal == SIGUSR1)
		c |= 1 << bit;
	bit++;
	if (bit == 8)
	{
		if (handle_char(c, &my_str))
			return (restart_server(0, &my_str, &bit, &c));
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	act;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &handler_usr;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
