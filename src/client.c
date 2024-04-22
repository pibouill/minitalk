/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/22 15:21:15 by pibouill         ###   ########.fr       */
/*   Updated: 2024/04/11 17:58:40 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int sig)
{
	(void)sig;
	ft_printf("Message acknowledged by the server and signal sent back.\n");
	exit(EXIT_SUCCESS);
}

void	send_bits(char bit, int server_pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((bit >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(400);
		i--;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	size_t					i;
	int					server_pid;

	if (ac == 3)
	{
		sa.sa_handler = sig_handler;
		i = 0;
		server_pid = ft_atoi(av[1]);
		sigaction(SIGUSR2, &sa, NULL);
		while (1)
		{
			while (i <= ft_strlen(av[2]))
			{
				send_bits(av[2][i], server_pid);
				i++;
			}
			pause();
		}
	}
	else
		ft_printf("Usage: ./client <PID> <string to send>\n");
	return (0);
}
