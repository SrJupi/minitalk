/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:05:25 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/04/11 12:57:44 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	clean_str(t_str *my_str)
{
	if (my_str->str != NULL)
		free(my_str->str);
	ft_bzero(my_str, sizeof(t_str));
}

int	alloc_mem(size_t size, t_str *my_str)
{
	my_str->str = (char *) malloc (size);
	if (my_str->str == NULL)
		return (1);
	ft_bzero(my_str->str, size);
	my_str->m_alloc = size;
	return (0);
}

int	add_char(char c, t_str *my_str)
{
	if (my_str->i >= my_str->m_alloc - 1)
		return (1);
	my_str->str[my_str->i] = c;
	my_str->i += 1;
	return (0);
}

int	print_message(int err)
{
	if (err == 0)
		return (0);
	ft_putstr_fd("Error: ", 2);
	if (err == 1)
		ft_putstr_fd("string is not same size\n", 2);
	if (err == 2)
		ft_putstr_fd("checksum is not the same\n", 2);
	if (err == 3)
		ft_putstr_fd("write error\n", 2);
	return (1);
}

int	print_str(t_str *my_str)
{
	int	err;

	err = 0;
	if (my_str->m_alloc != ft_strlen(my_str->str) + 1)
		err = 1;
	else if (my_str->check != ft_checksum(my_str->str))
		err = 2;
	else if (ft_putstr_fd(my_str->str, 1) == -1)
		err = 3;
	else if (ft_putchar_fd('\n', 1) == -1)
		err = 3;
	clean_str(my_str);
	return (print_message(err));
}
