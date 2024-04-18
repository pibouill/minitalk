/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 15:04:11 by pibouill          #+#    #+#             */
/*   Updated: 2024/04/18 18:55:43 by pibouill         ###   ########.fr       */
/*   Updated: 2024/04/11 17:58:40 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*int	g_receiver_flag = 0;*/

/*void	char_to_bin(char c, int pid)*/
/*{*/
	/*int	bit;*/

	/*bit = 0;*/
	/*while (bit < 8)*/
	/*{*/
		/*if (c & (bit << 1))*/
			/*kill(pid, SIGUSR1);*/
		/*else*/
			/*kill(pid, SIGUSR2);*/
		/*usleep(100);*/
		/*bit++;*/
	/*}*/
/*}*/

/*void	sig_handler(int signum, siginfo_t *info, void *context)*/
/*{*/
	/*(void)context;*/
	/*(void)info;*/
	/*if (signum == SIGUSR1)*/
	/*{*/
		/*ft_printf("String received.\n");*/
		/*exit(EXIT_SUCCESS);*/
	/*}*/
/*}*/

void	send_resp(int signum)
{
	/*g_receiver_flag = 1;*/
	if (signum == SIGUSR2)
		ft_printf("Message received.\n");
}

void	send_bit(int pid, int bit)
{
	int	sig;

	if (bit == 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	if (kill(pid, sig) == -1)
	{
		ft_printf("Sending Error.\n");
		exit(EXIT_FAILURE);
	}
	/*while (g_receiver_flag == 0)
		;
	g_receiver_flag = 0;*/
}

void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (c >> i) & 1);
		usleep(100);
		i--;
	}
}

void	send_str(int pid, const char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

int	main(int ac, char **av)
{
	pid_t		client_pid;

	if (ac == 3) 
	{
		client_pid = ft_atoi(av[1]);
		if (client_pid <= 0)
		{
			ft_printf("Invalid PID\n");
			exit(EXIT_FAILURE);
		}
		signal(SIGUSR1, send_resp);
		signal(SIGUSR2, send_resp);
		send_str(client_pid, av[2]);
	}
	else
		ft_printf("Usage: ./client <server PID> <string to send>");
	return (0);
}
