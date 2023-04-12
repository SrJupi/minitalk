/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:12:33 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/04/12 11:23:03 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_isserver = 0;

static void	handle_sig(int sig)
{
	usleep(200);
	if (!g_isserver && sig == SIGUSR1)
		g_isserver = 1;
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("\nError sending message!\n", 2);
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
	if (check_args(argc, argv))
		return (1);
	if (check_server(ft_atoi(argv[1])))
		return (not_server_error());
	if (!g_isserver)
		return (not_server_error());
	if (handle_str(ft_atoi(argv[1]), argv[2]))
	{
		ft_putstr_fd("\nError sending the message!\n", 2);
		return (1);
	}
	return (0);
}
