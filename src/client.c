/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/08 14:53:16 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receiver_flag;

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	static int	read_bit;

	g_receiver_flag = 1;
	if (signum == SIGUSR1)
		ft_printf("Number of bytes received: %dBs\n", read_bit);
	else if (signum == SIGUSR2)
		read_bit++;
}

int	char_to_bin(char c, int pid)
{
	int	i;
	int	bit_i;

	i = 0;
	bit_i = 7;
	while (bit_i >= 0)
	{
		if ((c >> bit_i) & 1 == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_receiver_flag == 0)
		{
			if (i == 50)
			{
				ft_printf("No response from server. Exiting.");
				exit(EXIT_FAILURE);
			}
			i++;
			usleep(100);
		}
		g_receiver_flag = 0;
	}
	return (0);
}

int	main(int ac, char **av)
{
	struct sigaction sa;
	int	client_pid;
	int i;

	if (ac == 3)
	{
		client_pid = ft_atoi(av[1]);
		sigemptyset(&sa.sa_mask);
		sa.sa_handler = sig_handler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, sa, NULL);
		sigaction(SIGUSR2, sa, NULL);
		i = -1;
		while (av[2][i++])
			char_to_bin(av[2][i], client_pid);
		char_to_bin('\0', client_pid);
	}
	return (0);
}
