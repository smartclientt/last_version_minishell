# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 19:08:56 by ael-idri          #+#    #+#              #
#    Updated: 2022/12/25 20:06:23 by shbi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC    =    ft_atoi.c    \
        ft_isalpha.c    \
        ft_memchr.c    \
        ft_memset.c    \
        ft_strjoin.c    \
        ft_strncmp.c    \
        ft_substr.c    \
        ft_bzero.c    \
        ft_isascii.c    \
        ft_memcmp.c    \
        ft_split.c    \
        ft_strlcat.c    \
        ft_strnstr.c    \
        ft_tolower.c    \
        ft_calloc.c    \
        ft_isdigit.c    \
        ft_memcpy.c    \
        ft_strchr.c    \
        ft_strlcpy.c    \
        ft_strrchr.c    \
        ft_toupper.c    \
        ft_isalnum.c    \
        ft_isprint.c    \
        ft_memmove.c    \
        ft_strdup.c    \
        ft_strlen.c    \
        ft_strtrim.c    \
		ft_itoa.c      \
		ft_strmapi.c   \
		ft_striteri.c  \
		ft_putchar_fd.c \
		ft_putstr_fd.c   \
		ft_putendl_fd.c   \
		ft_putnbr_fd.c  \

SRC_B = $(SRC) ft_lstnew.c ft_lstadd_front.c  ft_lstsize.c ft_lstlast.c	ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c	\
    
OBJ_B = $(SRC_B:.c=.o)

OBJS = $(SRC:.c=.o)

CC = cc

RM = rm -f

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

all: $(NAME)

%.o : %.c libft.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJ_B)

fclean: clean
	$(RM) $(NAME)

bonus: $(OBJ_B)
	ar rcs $(NAME) $(OBJ_B)


re: fclean $(NAME)

.PHONY = all clean fclean re bonus