/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pibouill <pibouill@student.42prague.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:40:26 by pibouill          #+#    #+#             */
/*   Updated: 2024/01/25 15:10:32 by pibouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_char(char c)
{
	return ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int	ft_atoi_base(const char *str, unsigned int base)
{
	int	ret = 0;
	int	sign = 1;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && is_valid_char(*str))
	{
		if (*str >= '0' && *str <= '9')
			ret = ret * base + *str - '0';
		if (*str >= 'a' && *str <= 'f')
			ret = ret * base + *str - 'a' + 10;
		if (*str >= 'A' && *str <= 'F')
			ret = ret * base + *str - 'A' + 10;
		str++;
	}
	return (ret * sign);
}
		
