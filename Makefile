# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/24 23:20:45 by keddib            #+#    #+#              #
#    Updated: 2020/11/10 03:25:37 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#-g -fsanitize=address

SRC = main.c projaction_3d.c cast_rays.c mlx_cub_utils.c hundle_keys.c incept.c\
read_file.c textures.c sprites.c bmp_file.c errors.c file_elements.c \
initializer.c utils/get_next_line.c utils/ft_split.c utils/cub_utils_two.c\
utils/cub_utils.c utils/cub_utils_three.c

FLAGS =  -lmlx -lXext -lX11 -lm

GO = clang

all:
	@$(GO) -g $(SRC) -o cub3d $(FLAGS) -D BONUS=0

clean:
	@rm -rf cub3d img.bmp

fclean: clean

re: fclean all

bonus:
	@$(GO) $(SRC) -o cub3d $(FLAGS) -D BONUS=1
