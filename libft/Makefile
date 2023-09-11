# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/01 17:44:14 by tguerin           #+#    #+#              #
#    Updated: 2022/11/23 21:57:38 by tguerin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

SRCS = ft_isalpha.c \
		ft_isalnum.c \
		ft_isdigit.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_strlcat.c \
		ft_strncmp.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putendl_fd.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_power.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_printf_utils.c \
		ft_printf/ft_printf_utils2.c \
		get_next_line/get_next_line.c

RPATH := `realpath --relative-to=${PWD} ${CURDIR}`/
RPATH := ${shell if [ "${RPATH}" != "./" ]; then echo ${RPATH}; fi}
NORMAL := ${shell tput sgr0}
RED := ${shell tput setaf 1}
GREEN := ${shell tput setaf 2}
BLUE := ${shell tput setaf 4}

OBJS	= ${SRCS:.c=.o}
NAME	:= libft.a
CC		:= clang
CFLAGS	:= -Wall -Wextra -Werror -g

.c.o:
			@${CC} -c ${CFLAGS} $< -o ${<:.c=.o}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}$<$(NORMAL)\n"

${NAME}:	${OBJS}
			@ar rc ${NAME} ${OBJS}
			@printf "$(BLUE)[$(GREEN)+$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

clean:
			@${RM} ${OBJS}
			@${foreach OBJ, ${OBJS}, \
				printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${OBJ}$(NORMAL)\n" ;}

fclean:		clean
			@${RM} ${NAME}
			@printf "$(BLUE)[$(RED)-$(BLUE)]$(BLUE) ${RPATH}${NAME}$(NORMAL)\n"

re:			fclean all

all:		${NAME}

.PHONY: clean, fclean, re, all
