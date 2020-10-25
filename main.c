/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/25 23:31:52 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x < g_window.width && x >= 0 && y < g_window.height && y >= 0)
		*(unsigned int *)dst = color;
}

int update(t_texture *tex)
{
	mlx_destroy_image(mlx.pointer, mlx.image);
	mlx.image = mlx_new_image(mlx.pointer, g_window.width, g_window.height);
	mlx.addr = mlx_get_data_addr(
		mlx.image,
		&mlx.bits_per_pixel,
		&mlx.line_length,
		&mlx.endian);
	update_player();
	cast_all_rays(tex);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		ft_exit(2);
	t_texture tex;
	mlx.pointer = mlx_init();
	read_file(argv[1], &tex);
	load_images(&tex);
	mlx.window = mlx_new_window(
		mlx.pointer,
		g_window.width,
		g_window.height,
		"Cub3d");
	mlx.image = mlx_new_image(mlx.pointer, g_window.width, g_window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_hook(mlx.window, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(mlx.window, 3, (1L << 1), key_released, (void *)0);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	mlx_loop_hook(mlx.pointer, update, &tex);
	mlx_loop(mlx.pointer);
	return 0;
}
