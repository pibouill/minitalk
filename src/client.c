/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:29:33 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/25 13:19:31 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum)
{
	(void)signum;
	ft_printf("Message acknowledged by the server and signal sent back.\n");
	exit(EXIT_SUCCESS);
}

void	pid_check(int server_pid)
{
	if (kill(server_pid, SIGUSR1) == -1)
	{
		ft_printf("Error. Verify PID.\n");
		exit(EXIT_FAILURE);
	}
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
	size_t				message_len;
	pid_t				server_pid;

	if (ac == 3)
	{
		sa.sa_handler = sig_handler;
		i = 0;
		message_len = ft_strlen(av[2]);
		server_pid = ft_atoi(av[1]);
		pid_check(server_pid);
		sigaction(SIGUSR2, &sa, NULL);
		while (1)
		{
			while (i <= message_len)
				send_bits(av[2][i++], server_pid);
			pause();
		}
	}
	else
		ft_printf("Usage: ./client <PID> <string to send>\n");
	return (0);
}
