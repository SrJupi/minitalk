/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:42:37 by lsulzbac          #+#    #+#             */
/*   Updated: 2023/02/15 12:42:09 by lsulzbac         ###   ########.fr       */
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
	int		m_alloc;
	int		i;
	int		pid;
}	t_str;

int		print_str(t_str *my_str);
int		add_char(char c, t_str *my_str);
void	clean_str(char **str);

int		check_pid(char *pid_str);
int		check_args(int argc, char **argv);
int		check_server(int pid);

int		param_error(void);
int		pid_error(void);
int		empty_str_error(void);
int		not_server_error(void);


#endif
