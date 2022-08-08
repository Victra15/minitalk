/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:36:22 by yolee             #+#    #+#             */
/*   Updated: 2022/08/09 00:30:08 by yolee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_and_initialize(char **printed_str,
		int *input_loop,
		int *str_size_cnt)
{
	if (*printed_str != NULL)
	{
		ft_printf("%s\n", (*printed_str));
		free(*printed_str);
		(*printed_str) = NULL;
	}
	(*input_loop) = 0;
	(*str_size_cnt) = 0;
}

void	resize_print_buf(char **buf, int *size_cnt)
{
	char	*temp;

	temp = (*buf);
	(*size_cnt)++;
	(*buf) = (char *)malloc(sizeof(char) * PRINT_BUFFER_SIZE * (*size_cnt));
	if (temp != NULL)
	{
		ft_memmove((*buf), temp, PRINT_BUFFER_SIZE * ((*size_cnt) - 1));
		free(temp);
	}
}

void	receive_signal(int signum)
{
	static char	*printed_str = NULL;
	static int	input_loop = 0;
	static int	str_size_cnt = 0;
	static char	received_char = 0;
	static int	binary_digit = 1;

	if (signum == SIGUSR2)
		received_char += binary_digit;
	binary_digit = binary_digit * 2;
	if (binary_digit == 256)
	{
		if (str_size_cnt * PRINT_BUFFER_SIZE <= input_loop)
			resize_print_buf(&printed_str, &str_size_cnt);
		printed_str[input_loop] = received_char;
		input_loop++;
		if (received_char == '\0')
			print_and_initialize(&printed_str, &input_loop, &str_size_cnt);
		received_char = 0;
		binary_digit = 1;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	pid = getpid();
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	action.sa_handler = receive_signal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_printf("%d\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
