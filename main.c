/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/22 14:48:04 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int update(t_texture *tex)
{
	mlx_destroy_image(mlx.pointer, mlx.image);
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	// map_render();
	// render_player(player.x, player.y);
	update_player();
	cast_all_rays(tex);
	// for (int i = 0; i < window.width; i++)
	// {
	// 	render_ray(&rays[i]);
	// }
	// render_3d_projection(rays, tex);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	return 0;
}

int main()
{
	t_texture tex;
	mlx.pointer = mlx_init();
	read_file("map.cub");
	load_images(&tex);

	mlx.window = mlx_new_window(mlx.pointer, window.width, window.height, "Cub3d");
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_hook(mlx.window, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(mlx.window, 3, (1L << 1), key_released, (void *)0);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	mlx_loop_hook(mlx.pointer, update, &tex);
	mlx_loop(mlx.pointer);
	return 0;
}
