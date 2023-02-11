/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:22 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/10 13:16:57 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_str	g_str;

static int	expand_str(void)
{
	char	*tmp;

	if (g_str.m_alloc == 0)
	{
		g_str.str = (char *) malloc (512);
		if (g_str.str == NULL)
			return (1);
		ft_bzero(g_str.str, 512);
		g_str.m_alloc = 512;
		return (0);
	}
	tmp = (char *) malloc (g_str.m_alloc * 2);
	if (tmp == NULL)
	{
		free(g_str.str);
		g_str.str = NULL;
		return (1);
	}
	ft_bzero(tmp, g_str.m_alloc * 2);
	ft_strlcpy(tmp, g_str.str, g_str.m_alloc);
	g_str.str = tmp;
	g_str.m_alloc *= 2;
	return (0);
}

static int	add_char(char c)
{
	if (g_str.i >= g_str.m_alloc - 1)
	{
		if (expand_str())
			return (1);
	}
	g_str.str[g_str.i] = c;
	g_str.i++;
	return (0);
}

static int	print_str(void)
{
	int	i;

	i = 0;
	while (i < g_str.i)
	{
		if (write(1, &g_str.str[i], 1) == -1)
			return (1);
		i++;
	}
	free(g_str.str);
	g_str.m_alloc = 0;
	g_str.i = 0;
	return (0);
}

static void	handle_char(char c, siginfo_t *info)
{
	if (c)
	{
		if (add_char(c))
		{
			kill(info->si_pid, SIGUSR2);
			exit (1);
		}
	}
	else
	{
		if (print_str())
		{
			kill(info->si_pid, SIGUSR2);
			exit (1);
		}
	}
}

static void	handler_usr(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static char	c;

	(void)context;
	usleep(50);
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else
		c |= 0 << bit;
	bit++;
	if (bit == 8)
	{
		handle_char(c, info);
		bit = 0;
		c = 0;
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
