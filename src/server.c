/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:03:44 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/25 13:30:43 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"
#include <bits/types/siginfo_t.h>

void	handle_message(char c, char **message, size_t *msg_len,
			siginfo_t *siginfo)
{
	if (c == 0)
	{
		if (*message)
		{
			write(1, *message, *msg_len);
			write(1, "\n", 1);
			free(*message);
			*message = NULL;
			*msg_len = 0;
		}
		kill(siginfo->si_pid, SIGUSR2);
	}
	else
	{
		*message = ft_realloc(*message, *msg_len, *msg_len + 1);
		(*message)[*msg_len] = c;
		(*msg_len)++;
	}
}

void	sig_handler(int signum, siginfo_t *siginfo, void *context)
{
	static int		bit;
	static char		c;
	static char		*message;
	static size_t	msg_len;

	(void)context;
	if (bit == 0)
		bit = 8;
	bit--;
	if (signum == SIGUSR1)
		c &= ~(1 << bit);
	else if (signum == SIGUSR2)
		c |= (1 << bit);
	if (bit == 0)
	{
		handle_message(c, &message, &msg_len, siginfo);
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
