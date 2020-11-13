# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/24 23:20:45 by keddib            #+#    #+#              #
#    Updated: 2020/11/13 20:02:31 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = main.c projaction_3d.c cast_rays.c mlx_cub_utils.c hundle_keys.c incept.c\
read_file.c textures.c sprites.c bmp_file.c errors.c file_elements.c\
initializer.c utils/get_next_line.c utils/ft_split.c utils/cub_utils_two.c\
utils/cub_utils.c utils/cub_utils_three.c

OBJS = main.o projaction_3d.o cast_rays.o mlx_cub_utils.o hundle_keys.o incept.o\
read_file.o textures.o sprites.o bmp_file.o errors.o file_elements.o\
initializer.o utils/get_next_line.o utils/ft_split.o utils/cub_utils_two.o\
utils/cub_utils.o utils/cub_utils_three.o

FLAGS =  -lmlx -framework OpenGL -framework AppKit -lm

GO = gcc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)  -D BONUS=0
	@$(GO)  -D BONUS=0 -c $(SRCS)
	@$(GO)  -D BONUS=0 -o$(NAME) $(OBJS) $(FLAGS)

clean :
		rm -f ${OBJS}

fclean : clean
		rm -f $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
