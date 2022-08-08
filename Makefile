# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yolee <yolee@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 22:20:24 by yolee             #+#    #+#              #
#    Updated: 2022/08/08 23:44:39 by yolee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra
NAME = server
C_NAME = client
OBJS = server.o \
	client.o \
	
HEADER_FLAG = -I ft_printf/srcs -I ft_printf/libft
PRINTF_DIR = ft_printf

all :  
	$(MAKE) -C $(PRINTF_DIR)
	$(MAKE) $(C_NAME)
	$(MAKE) $(NAME)

$(NAME) : server.o
	$(CC) $(CFLAGS) $< -I $(PRINTF_DIR) -L$(PRINTF_DIR) -lftprintf -o $(NAME)
	
$(C_NAME) : client.o
	$(CC) $(CFLAGS) $< -I $(PRINTF_DIR) -L$(PRINTF_DIR) -lftprintf -o $(C_NAME)

server.o : server.c
	$(CC) $(CFLAGS) $(HEADER_FLAG) -c $< -o $@

client.o : client.c
	$(CC) $(CFLAGS) $(HEADER_FLAG) -c $< -o $@

clean :
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(C_NAME)

re : fclean all

.phony : all clean fclean re