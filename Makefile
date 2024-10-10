NAME				:=		minishell
PATH_SRC			:=		src
PATH_BUILD			:=		build
PATH_LIBFT			:=		libft
SRCS				:=		$(shell find $(PATH_SRC) -name *.c)
OBJS				:=		$(SRCS:%.c=$(PATH_BUILD)/%.o)
DEPS				:=		$(OBJS:.o=.d)
INC_DIRS			:=		$(shell find $(PATH_SRC) -type d)

CC					:=		gcc
MACOSX_DEPLOYMENT_TARGET := 11.1
FLAGS_COMP			:= 		-Wall -Wextra -Werror -g -I$(INC_DIRS) -MMD -MP
FLAGS_LINKING		:=		-L$(PATH_LIBFT) -lft -lncurses -ltermcap -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline
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

all:						$(NAME)
							@ printf "$(_SUCCESS) Compilation done\n"
							@ printf "$(_ASCII_ART)"

$(NAME):					$(OBJS)
							@ $(MAKE) -C $(PATH_LIBFT)  # Build libft first
							@ $(CC) $(FLAGS_COMP) -o $@ $(OBJS) $(FLAGS_LINKING)

$(PATH_BUILD)/%.o:			%.c
							@ mkdir -p $(dir $@)
							@ $(CC) $(FLAGS_COMP) -c $< -o $@

clean:
							@ $(RM) $(PATH_BUILD)
							@ make -C $(PATH_LIBFT) clean
							@ printf "$(_INFO) Deleted files and directory\n"

fclean:						clean
							@ $(RM) $(NAME)
							@ make -C $(PATH_LIBFT) fclean

re:							fclean all

.PHONY:						all clean fclean re

-include $(DEPS)
