/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:05:25 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/15 12:47:15 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	clean_str(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

static int	expand_str(t_str *my_str)
{
	char	*tmp;

	if (my_str->m_alloc == 0)
	{
		my_str->str = (char *) malloc (512);
		if (my_str->str == NULL)
			return (1);
		ft_bzero(my_str->str, 512);
		my_str->m_alloc = 512;
		return (0);
	}
	tmp = (char *) malloc (my_str->m_alloc * 2);
	if (tmp == NULL)
	{
		clean_str(&my_str->str);
		return (1);
	}
	ft_bzero(tmp, my_str->m_alloc * 2);
	ft_strlcpy(tmp, my_str->str, my_str->m_alloc);
	clean_str(&my_str->str);
	my_str->str = tmp;
	my_str->m_alloc *= 2;
	tmp = NULL;
	return (0);
}

int	add_char(char c, t_str *my_str)
{
	if (my_str->i >= my_str->m_alloc - 1)
	{
		if (expand_str(my_str))
			return (1);
	}
	my_str->str[my_str->i] = c;
	my_str->i += 1;
	return (0);
}

int	print_str(t_str *my_str)
{
	if (ft_putstr_fd(my_str->str, 1) == -1)
		return (1);
	if (ft_putchar_fd('\n', 1) == -1)
		return (1);
	clean_str(&my_str->str);
	my_str->m_alloc = 0;
	my_str->i = 0;
	my_str->pid = 0;
	return (0);
}
