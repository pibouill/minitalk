/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:03:20 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/24 16:00:24 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct info
{
	int		flag;
	int		bit;
	char	c;
	pid_t	server_pid;
}				t_info;

#endif
