/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:16:31 by yolee             #+#    #+#             */
/*   Updated: 2022/08/09 00:39:10 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_char_as_signal(int pid, char chr)
{
	int	loop;

	loop = 0;
	while (loop < 8)
	{
		if (chr % 2 == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		chr = chr / 2;
		loop++;
		usleep(500);
	}
}

void	send_string_as_signal(int pid, char *str)
{
	int	len;
	int	loop;

	len = ft_strlen(str);
	loop = 0;
	while (loop <= len)
	{
		send_char_as_signal(pid, str[loop]);
		usleep(500);
		loop++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		ft_printf("invalid argument number");
	else
	{
		send_string_as_signal(ft_atoi(argv[1]), argv[2]);
	}
	return (0);
}
