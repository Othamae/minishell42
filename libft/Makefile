# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vconesa- <vconesa-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/24 10:02:11 by vconesa-          #+#    #+#              #
#    Updated: 2024/07/21 10:58:39 by vconesa-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = cc
CREATELIB = ar rc
SOURCES = $(shell ls *.c)
OBJECTS = ${SOURCES:.c=.o}

.c.o: $(SRCS)
	${CC} ${FLAGS} -c -o $@ $<

all: ${NAME}

${NAME} : ${OBJECTS}
		${CREATELIB} ${NAME} ${OBJECTS}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all