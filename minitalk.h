/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:42:37 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/03/28 10:46:58 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct t_str
{
	char	*str;
	size_t	m_alloc;
	size_t	i;
	char	check;
	int		pid;
}	t_str;

int		receive_size(int signal, t_str *my_str);
int		receive_check(int signal, t_str *my_str);
int		receive_char(int signal, t_str *my_str);

int		handle_str(int pid, char *str);

char	ft_checksum(char *str);

int		print_str(t_str *my_str);
int		add_char(char c, t_str *my_str);
int		alloc_mem(size_t size, t_str *my_str);
void	clean_str(t_str *my_str);

int		check_pid(char *pid_str);
int		check_args(int argc, char **argv);
int		check_server(int pid);

int		param_error(void);
int		pid_error(void);
int		empty_str_error(void);
int		not_server_error(void);

#endif
