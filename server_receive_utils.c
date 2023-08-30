/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_receive_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:36:28 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/08/30 18:51:37 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	receive_size(int signal, t_str *my_str)
{
	static size_t	size;
	static size_t	bit;

	if (signal == SIGUSR1)
		size |= 1 << bit;
	bit++;
	if (bit == (sizeof(size_t) * 8))
	{
		bit = 0;
		if (alloc_mem(size + 1, my_str))
		{
			size = 0;
			return (1);
		}
		size = 0;
	}
	return (0);
}

int	receive_check(int signal, t_str *my_str)
{
	static char		c;
	static size_t	bit;

	if (signal == SIGUSR1)
		c |= 1 << bit;
	bit++;
	if (bit == (sizeof(char) * 8))
	{
		my_str->check = c;
		c = 0;
		bit = 0;
	}
	return (0);
}

int	receive_char(int signal, t_str *my_str)
{
	static char		c;
	static size_t	bit;
	int				ret;

	ret = 0;
	if (signal == SIGUSR1)
		c |= 1 << bit;
	bit++;
	if (bit == (sizeof(char) * 8))
	{
		if (c)
		{
			if (add_char(c, my_str))
				ret = 1;
		}
		else
		{
			if (print_str(my_str))
				ret = 1;
		}
		c = 0;
		bit = 0;
	}
	return (ret);
}
