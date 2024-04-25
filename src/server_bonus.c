/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:03:44 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/25 13:30:24 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sig_handler(int signum, siginfo_t *siginfo, void *context)
{
	static int	flag = 0;
	static int	bit = 8;
	static char	c = 0;

	(void)context;
	if (signum == SIGUSR1)
		flag = 0;
	else if (signum == SIGUSR2)
		flag = 1;
	bit--;
	c += (flag << bit);
	if (bit == 0)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			kill(siginfo->si_pid, SIGUSR2);
		}
		write(1, &c, 1);
		bit = 8;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				server_pid;

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
