# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mac <mac@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/11 16:52:40 by vconesa-          #+#    #+#              #
#    Updated: 2024/11/28 13:37:59 by mac              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				:=      minishell
PATH_SRC				:=      src
PATH_BUILD          :=      ./build
LIBFT_PATH          :=      ./libft
LIBFT               :=      $(LIBFT_PATH)/libft.a
SRCS                :=      $(shell find $(PATH_SRC) -name *.c) # TODO: List the files .c
OBJS                :=      $(SRCS:$(PATH_SRC)/%.c=$(PATH_BUILD)/%.o)
INC_DIRS            :=      ./include

CC                  :=      gcc
FLAGS               :=      -g -Wall -Wextra -Werror

# Readline paths
READLINE_LIB        :=      /usr/local/Cellar/readline/8.2.10/lib
READLINE_INC        :=      /usr/local/Cellar/readline/8.2.10/include

# Link readline and ncurses for macOS
FLAGS_LIB           :=      -L$(READLINE_LIB) -lreadline -lncurses
INCLUDES            :=      -I$(READLINE_INC) -I$(INC_DIRS)

RM                  :=      rm -rf

_YELLOW             :=      \e[38;5;184m
_GREEN              :=      \e[38;5;46m
_RESET              :=      \e[0m
_INFO               :=      [$(_YELLOW)INFO$(_RESET)]
_SUCCESS            :=      [$(_GREEN)SUCCESS$(_RESET)]
_ASCII_GREEN        :=      \e[38;5;46m
_ASCII_ART          :=      $(_ASCII_GREEN)       ██████   ██████  ███      ███        █████    ████  ████\n\
							░░██████ ██████  ░░              ░░░          ░░███               ░░███ ░░███\n\
							░███░█████░███  ████  ████████   ████   █████  ░███████    ██████  ░███  ░███\n\
							░███░░███ ░███ ░░███ ░░███░░███ ░░███  ███░░   ░███░░███  ███░░███ ░███  ░███\n\
							░███ ░░░  ░███  ░███  ░███ ░███  ░███ ░░█████  ░███ ░███ ░███████  ░███  ░███\n\
							░███      ░███  ░███  ░███ ░███  ░███  ░░░░███ ░███ ░███ ░███░░░   ░███  ░███\n\
							█████     █████ █████ ████ █████ █████ ██████  ████ █████░░██████  █████ █████\n\
							░░░░░     ░░░░░ ░░░░░ ░░░░ ░░░░░ ░░░░░ ░░░░░ ░░░░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░ $(_RESET)\n

$(PATH_BUILD)/%.o: $(PATH_SRC)/%.c
							mkdir -p $(dir $@)
							$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<

all:						$(NAME)
							@ printf "$(_SUCCESS) Compilation done\n"
							@ printf "$(_ASCII_ART)"

$(NAME):					$(LIBFT) $(OBJS)
							$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) $(FLAGS_LIB)

$(LIBFT):
							make -C $(LIBFT_PATH) all

clean:
							make -C $(LIBFT_PATH) clean
							$(RM) $(OBJS)

fclean:						clean
							make -C $(LIBFT_PATH) fclean
							$(RM) $(NAME)

re:							fclean all

.PHONY:						all clean fclean re

