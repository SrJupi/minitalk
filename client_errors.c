/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:34:14 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/03/28 10:34:16 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	param_error(void)
{
	ft_putstr_fd("Error. Client takes two parameters:\n", 2);
	ft_putstr_fd("./client [SERVER_PID] [Message]\n", 2);
	return (1);
}

int	pid_error(void)
{
	ft_putstr_fd("Error. PID not valid!\n", 2);
	return (1);
}

int	empty_str_error(void)
{
	ft_putstr_fd("Error. Trying to send empty string!\n", 2);
	return (1);
}

int	not_server_error(void)
{
	ft_putstr_fd("Error. Server not found!\n", 2);
	return (1);
}
