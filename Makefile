# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: labintei <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 14:05:41 by labintei          #+#    #+#              #
#    Updated: 2021/10/28 18:29:18 by mlaouedj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	src/main.c			\
			src/ft_utils.c			\
			src/ft_draw.c			\
			src/ft_keycode.c		\
			src/ft_frame.c			\
			src/parsing/ft_map_01.c 	\
			src/parsing/ft_map_02.c 	\
			src/parsing/ft_text_parsing.c 	\
			src/parsing/ft_map_parsing.c	\
			src/ray_casting/ft_ray.c 	\
			src/ray_casting/ft_ray_01.c	\
			src/ray_casting/ft_direction.c	\
			src/ray_casting/ft_se.c		\
			src/ray_casting/ft_sw.c		\
			src/ray_casting/ft_nw.c		\
			src/ray_casting/ft_ne.c		\
			src/ray_casting/ft_texture.c	\
			gnl/get_next_line.c		\
			gnl/get_next_line_utils.c	\
			
DIR_MLX		=	./mlx_linux/

OBJS		= $(SRCS:.c=.o)

CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -g3 -fsanitize=address -I includes.
LIBS			= -L ./mlx_linux/ -lmlx -lXext -lX11 -lm
RM				= rm -f
NAME			= cub3D

all:		${NAME}
.c.o:
				${CC} ${CFLAGS} -Imlx -Ibass -c $< -o ${<:c=o}

$(NAME):	$(OBJS)
				make -C $(DIR_MLX)
				${CC} $(CFLAGS) -o $(NAME) $(SRCS) $(LIBS)

clean:
				make -C $(DIR_MLX) clean
				$(RM) $(OBJS)

fclean:			
				make -C $(DIR_MLX) clean
				$(RM) $(NAME)

re: clean all

.PHONY:		all clean fclean re
