/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:01 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/10 15:34:31 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received;

void	bin_to_char(int sig)
{
	static int	bit;
	static int	i;

	if (sig == SIGUSR1)
		i |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		g_received = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf("String received.\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	struct	sigaction sa;
	int		client_pid;

	(void)ac;
	(void)av;
	client_pid = getpid();
	ft_printf("Server PID: <%d>\n", client_pid);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
