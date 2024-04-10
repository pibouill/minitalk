/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/10 17:45:16 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_to_bin(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (bit << 1))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
	{
		ft_printf("String received.\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	struct	sigaction sa;
	int		client_pid;
	int		i;

	if (ac == 3 && ft_atoi(av[1]) > 0)
	{
		client_pid = ft_atoi(av[1]);
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = sig_handler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		i = 0;
		while (av[2][i])
		{
			char_to_bin(av[2][i], client_pid);
			i++;
		}
		sleep(5);
		ft_printf("Sending failed...");
	}
	else
		ft_printf("Usage: ./client <server PID> <string to send>");
	return (0);
}
