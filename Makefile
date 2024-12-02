# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 16:52:40 by vconesa-          #+#    #+#              #
#    Updated: 2024/12/01 19:37:55 by vconesa-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=		minishell
PATH_SRC			:=		src
PATH_BUILD			:=		./build
LIBFT_PATH 			:= 		./libft
LIBFT 				:= 		$(LIBFT_PATH)/libft.a
SRCS				:=		$(PATH_SRC)/exec.c \
							$(PATH_SRC)/free_cmd.c \
							$(PATH_SRC)/ft_qsort.c \
							$(PATH_SRC)/init_free_context.c \
							$(PATH_SRC)/inits.c \
							$(PATH_SRC)/main.c \
							$(PATH_SRC)/nulterminate.c \
							$(PATH_SRC)/parse_utils_2.c \
							$(PATH_SRC)/parse_utils.c \
							$(PATH_SRC)/parse.c \
							$(PATH_SRC)/pipe.c \
							$(PATH_SRC)/redir.c \
							$(PATH_SRC)/signal.c \
							$(PATH_SRC)/signal_herdoc.c \
							$(PATH_SRC)/token_utils.c \
							$(PATH_SRC)/token.c \
							$(PATH_SRC)/utils_2.c \
							$(PATH_SRC)/utils.c \
							$(PATH_SRC)/builtins/builtins.c \
							$(PATH_SRC)/builtins/cd_pwd.c \
							$(PATH_SRC)/builtins/echo_env.c \
							$(PATH_SRC)/builtins/echo_utils.c \
							$(PATH_SRC)/builtins/echo.c \
							$(PATH_SRC)/builtins/environ.c \
							$(PATH_SRC)/builtins/export_env_utils.c \
							$(PATH_SRC)/builtins/export_env.c \
							$(PATH_SRC)/bonus/andor_bonus.c \
							$(PATH_SRC)/bonus/inits_bonus.c \
							$(PATH_SRC)/bonus/wildcards_bonus.c \
							$(PATH_SRC)/bonus/wildcards_utils_bonus.c

OBJS				:=		$(SRCS:$(PATH_SRC)/%.c=$(PATH_BUILD)/%.o)
INC_DIRS			:=		./include

CC					:=		gcc # remove g
FLAGS 				:= 		-g -Wall -Wextra -Werror # remove g
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
							░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ $(_RESET)\n

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

bonus:						all
							@ printf "$(_SUCCESS) Bonus compilation done\n"

clean:
							make -C $(LIBFT_PATH) clean
							$(RM) $(OBJS)

fclean: 					clean
							make -C $(LIBFT_PATH) fclean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re bonus