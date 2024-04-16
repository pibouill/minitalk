/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:01 by pibouill          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/16 13:11:21 by pibouill         ###   ########.fr       */
=======
/*   Updated: 2024/04/11 17:38:49 by pibouill         ###   ########.fr       */
>>>>>>> 7d36b267f20ee26a3aa925e7c743329996d8dac0
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit_count;
	static pid_t			client_pid;

	(void)context;
	if (client_pid != info->si_pid)
	{
		bit_count = 0;
		c = 0;
	}
	client_pid = info->si_pid;
	c = c << 1;
	if (signum == SIGUSR1)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	(void)ac;
	(void)av;
	server_pid = getpid();
	ft_printf("Server PID: <%d>\n", server_pid);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
