/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:29:33 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/24 18:29:35 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum)
{
	(void)signum;
	ft_printf("Message acknowledged by the server and signal sent back.\n");
	exit(EXIT_SUCCESS);
}

void	send_bits(char bit, int server_pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (((bit >> i) & 1) == 1)
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
	size_t				i;
	pid_t				server_pid;

	if (ac == 3)
	{
		sa.sa_handler = sig_handler;
		i = 0;
		server_pid = ft_atoi(av[1]);
		sigaction(SIGUSR2, &sa, NULL);
		while (1)
		{
			while (i <= ft_strlen(av[2]))
				send_bits(av[2][i++], server_pid);
			pause();
		}
	}
	else
		ft_printf("Usage: ./client <PID> <string to send>\n");
	return (0);
}
