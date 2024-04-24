/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:00:27 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/24 23:00:38 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static t_info	g_info;

void	sig_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_info.flag = 0;
	else if (signum == SIGUSR2)
		g_info.flag = 1;
	g_info.bit--;
	g_info.c += (g_info.flag << g_info.bit);
	if (g_info.bit == 0)
	{
		if (g_info.c == 0)
		{
			ft_printf("\n");
			kill(siginfo->si_pid, SIGUSR2);
		}
		ft_printf("%c", g_info.c);
		g_info.bit = 8;
		g_info.c = 0;
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
	g_info.bit = 8;
	g_info.c = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
