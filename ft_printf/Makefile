# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/26 17:26:35 by shbi              #+#    #+#              #
#    Updated: 2022/03/23 04:30:50 by shbi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=		libftprintf.c libftprintf_tools1.c libftprintf_tools2.c libftprintf_tools3.c
OBJS	= 		$(SRCS:.c=.o)
CC		=		cc
CFLAGS	=		-Wall -Werror -Wextra
AR		=		ar -cr
RM		=		rm -rf
NAME	=		libftprintf.a
HEADER	=		ft_printf.h

all			:	$(NAME)
$(NAME)		:	$(OBJS)
				$(AR) $(NAME) $(OBJS)
%.o			:	%.c  $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@
clean		:
				$(RM) $(OBJS)
fclean		:	clean
				$(RM) $(NAME)
re			:	fclean all
.PHONY		:	all clean fclean re