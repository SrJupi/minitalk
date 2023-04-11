/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checksum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:36:19 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/03/28 10:36:20 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	ft_checksum(char *str)
{
	char	check;

	check = 0;
	while (*str)
	{
		check ^= *str;
		str++;
	}
	return (check);
}
