# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keddib <keddib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/24 23:20:45 by keddib            #+#    #+#              #
#    Updated: 2020/11/02 00:18:05 by keddib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#-g -fsanitize=address

SRC = main.c 3d.projection.c cast_rays.c cub_utils.c hundle_keys.c incept.c\
read_file.c textures.c utils/get_next_line.c utils/ft_split.c\
utils/cub_utils_two.c utils/cub_utils.c

PATH = -I /usr/local/include -L /usr/local/lib

FLAGS =  -lmlx -framework OpenGL -framework AppKit -lm

GO = gcc -Wall -Werror -Wextra

all:
	@$(GO)  $(SRC) -o cub3d $(PATH) $(FLAGS)

clean:
	@rm -rf cub3d

fclean: clean
	@rm -rf cud3d

re: fclean all

run:
	@./cub3d map.cub

