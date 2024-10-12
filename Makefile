# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 16:52:40 by vconesa-          #+#    #+#              #
#    Updated: 2024/10/12 12:39:18 by vconesa-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME				:=		minishell
PATH_SRC			:=		src
PATH_BUILD			:=		./build
LIBFT_PATH 			:= 		./libft
LIBFT 				:= 		$(LIBFT_PATH)/libft.a
SRCS				:=		$(shell find $(PATH_SRC) -name *.c) # TODO: List the files .c
OBJS				:=		$(SRCS:$(PATH_SRC)/%.c=$(PATH_BUILD)/%.o)
INC_DIRS			:=		./include

CC					:=		gcc
FLAGS 				:= 		-g -Wall -Wextra -Werror
FLAGS_LIB			:= 		-lreadline
RM					:=		rm -rf

_YELLOW				:=		\e[38;5;184m
_GREEN				:=		\e[38;5;46m
_RESET				:=		\e[0m
_INFO				:=		[$(_YELLOW)INFO$(_RESET)]
_SUCCESS			:=		[$(_GREEN)SUCCESS$(_RESET)]
_ASCII_GREEN		:=		\e[38;5;46m
_ASCII_ART			:=		$(_ASCII_GREEN)██████   ██████  ███              ███          █████               ████  ████\n\
                            ░░██████ ██████  ░░░              ░░░          ░░███               ░░███ ░░███\n\
                            ░███░█████░███  ████  ████████   ████   █████  ░███████    ██████  ░███  ░███\n\
                            ░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███\n\
                            ░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███\n\
                            ░███      ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███\n\
                            █████     █████ █████ ████ █████ █████ ██████  ████ █████░░██████  █████ █████\n\
                            ░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ ░░░░░$(_RESET)\n

$(PATH_BUILD)/%.o: $(PATH_SRC)/%.c
							mkdir -p $(dir $@)
							$(CC) $(FLAGS) -c -o $@ $<


all:						$(NAME)
							@ printf "$(_SUCCESS) Compilation done\n"
							@ printf "$(_ASCII_ART)"

$(NAME):					$(LIBFT) $(OBJS)
							$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(FLAGS_LIB)

$(LIBFT):
							make -C $(LIBFT_PATH) all

clean:						
							make -C $(LIBFT_PATH) clean
							$(RM) $(OBJS)

fclean: 					clean
							make -C $(LIBFT_PATH) fclean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
