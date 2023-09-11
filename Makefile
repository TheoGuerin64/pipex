# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 17:44:14 by tguerin           #+#    #+#              #
#    Updated: 2022/11/25 15:53:46 by tguerin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

SRCS :=		main.c \
			utils.c \
			utils2.c \
			parse.c \
			parse2.c \
			error.c \
			exec.c
FT_SRC :=	libft

RPATH		:= `realpath --relative-to=${PWD} ${CURDIR}`/
RPATH		:= ${shell if [ "${RPATH}" != "./" ]; then echo ${RPATH}; fi}
NORMAL		:= ${shell tput sgr0}
RED			:= ${shell tput setaf 1}
GREEN		:= ${shell tput setaf 2}
BLUE		:= ${shell tput setaf 4}

OBJS	:=	${SRCS:.c=.o}
NAME	:=	pipex
CC		:=	clang
CFLAGS	:=	-g -Wall -Wextra -Werror
FTFLAGS :=	-lft -L${FT_SRC}

.c.o:
			@${CC} -c ${CFLAGS} $< -o ${<:.c=.o}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}$<$(NORMAL)\n"

${NAME}:	${OBJS}
			@make -sC ${FT_SRC}
			@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${FTFLAGS}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

clean:
			@make -sC ${FT_SRC} clean
			@${RM} ${OBJS}
			@${foreach OBJ, ${OBJS}, \
				printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${OBJ}$(NORMAL)\n";}

fclean:
			@make -sC ${FT_SRC} fclean
			@${RM} ${OBJS}
			@${foreach OBJ, ${OBJS}, \
				printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${OBJ}$(NORMAL)\n";}
			@${RM} ${NAME}
			@printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

re:			fclean all

all:		${NAME}

.PHONY: clean, fclean, re, all
