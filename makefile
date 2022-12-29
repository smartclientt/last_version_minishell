# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shbi <shbi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 01:50:38 by shbi              #+#    #+#              #
#    Updated: 2022/12/29 02:26:34 by shbi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	minishell.c														\
				env_tools.c env_tools_.c tools.c								\
				b_echo.c b_cd.c b_env.c	b_pwd.c b_export.c b_unset.c			\
				error_case.c pipes.c check_cmd.c execution.c exec_builted.c		\
				minishell_loop.c redirection_execute.c signal_handler.c			\
				expand_exit_status.c expand.c ft_grammar.c ft_lexer.c			\
				heredoc.c list_struct.c t_string.c t_vector.c some_functions.c

OBJS		=	$(SRCS:.c=.o)
HEADR		=	minishell.h
LIBFT		=	./libft/libft.a
PATH_LIBFT	=	./libft
CC			=	cc
FLAGS		=	-Wall -Werror -Wextra -g
LDFLAGS		=	-lreadline
LDFLAGSS	=	-L /Users/${USER}/homebrew/opt/readline/lib
CPPFLAGS	=	-I /Users/${USER}/homebrew/opt/readline/include
RM			=	rm -rf

all			:	$(NAME)
				$(RM) $(OBJS)
$(LIBFT)	:
				@make bonus -C $(PATH_LIBFT)
$(NAME)		:	$(OBJS) $(LIBFT)
				$(CC) $(FLAGS) $(LDFLAGS) $(LDFLAGSS) -o $(NAME) $(OBJS) $(LIBFT)
%.o			:	%.c $(HEADR)
				$(CC) $(FLAGS) $(CPPFLAGS) -c $< -o $@
clean		:
				$(RM) $(OBJS)
				@make clean -C $(PATH_LIBFT)
fclean		:	clean
				$(RM) $(NAME)
				@make fclean -C $(PATH_LIBFT)
re			:	fclean all
				