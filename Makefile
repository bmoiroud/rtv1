# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoiroud <bmoiroud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 18:32:53 by bmoiroud          #+#    #+#              #
#    Updated: 2017/06/30 16:20:11 by bmoiroud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRCDIR = srcs

SRC_NAME =	main.c ft_init.c ft_check.c ft_parse.c ft_get_data.c ft_vector.c

SRC = $(addprefix ${SRCDIR}/, ${SRC_NAME})

OBJDIR = objs

OBJ = $(addprefix ${OBJDIR}/, $(SRC_NAME:.c=.o))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

MLX = mlx_sierra/

FRAMEWORKS = -framework OpenGL -framework AppKit

all:${NAME}

${NAME}: ${OBJ}
		@make -C libft/
		@make -C ${MLX}
		@${CC} ${CFLAGS} -I. -Ilibft/includes/ -I${MLX} -Llibft/ -lft -L${MLX} -lmlx ${FRAMEWORKS} -o $@ $^

${OBJDIR}/%.o: ${SRCDIR}/%.c
		@/bin/mkdir -p ${OBJDIR}
		@${CC} ${CFLAGS} -I. -Ilibft/includes/ -I${MLX} -c -o $@ $<

clean:
		@make -C ${MLX} clean
		@make -C libft/ clean
		@/bin/rm -Rf ${OBJDIR}

fclean: clean
		@make -C libft/ fclean
		@/bin/rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
