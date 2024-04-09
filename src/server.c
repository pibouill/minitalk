/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:01 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/09 17:19:26 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin_to_char(char *c, int signum)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c <<= 1;
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	static int	pid;
	static int	i;
	static char	c;

	(void)context;
	pid = info->si_pid;
	bin_to_char(&c, signum);
	if (++i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(pid, SIGUSR1);
			pid = 0;
			return ;
		}
		write(1, "c", 1);
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction sa;
	int	client_pid;

	(void)ac;
	(void)av;
	client_pid = getpid();
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
