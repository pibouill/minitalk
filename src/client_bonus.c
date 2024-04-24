/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:00:17 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/24 23:00:49 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sig_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)context;
	(void)siginfo;
	ft_printf("Message acknowledged by the server and signal sent back.\n");
	exit(EXIT_SUCCESS);
}

void	pid_check(int server_pid)
{
	if (kill(server_pid, SIGUSR1) == -1)
	{
		ft_printf("Error.\nVerify PID.\n");
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
		usleep(300);
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
		sa.sa_sigaction = sig_handler;
		i = 0;
		server_pid = ft_atoi(av[1]);
		pid_check(server_pid);
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
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
