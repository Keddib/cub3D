/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/05 23:10:55 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void render_3d_projection()
{
	for (int i = 0; i < window.num_rays; i++)
	{
		float correctWallDistance =
			rays[i].distance * cos(rays[i].ray_angle - player.rotation_angle);
		float distanceProjPlane = (window.width / 2) / tan(FOV_ANGLE / 2);
		float wallHieght = (window.tile_size / correctWallDistance) * distanceProjPlane;
		int wallStripeHieght = (int)wallHieght;
		int wallTopPixel = (window.height / 2) - (wallStripeHieght / 2);
		if (wallTopPixel < 0)
			wallTopPixel = 0;
		int wallBottomPixel = (window.height / 2) + (wallStripeHieght / 2);
		if (wallBottomPixel > window.height)
			wallBottomPixel = window.height;

		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			int color = rays[i].was_hit_vertical ? 0xd3d3d3 : 0xffffff;
			my_mlx_pixel_put(&mlx, i, y, color);
		}
		for (int c = 0; c < wallTopPixel; c++)
			my_mlx_pixel_put(&mlx, i, c, 0x5cabf4);
		for (int f = wallBottomPixel; f < window.height; f++)
			my_mlx_pixel_put(&mlx, i, f, 0xc58b00);
	}
}

int update(void *param)
{
	mlx_destroy_image(mlx.pointer, mlx.image);
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_new_image(mlx.pointer, window.width, window.height);
	//map_render();
	update_player();
	//render_player(player.x, player.y);
	cast_all_rays();
	// for (int i = 0; i < window.num_rays; i++)
	// {
	// 	render_ray(i);
	// }
	render_3d_projection();
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	return 0;
}

int main()
{
	mlx.pointer = mlx_init();
	read_file("map.cub");
	mlx.window = mlx_new_window(mlx.pointer, window.width, window.height, "Cub3d");
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	setup_player();
	mlx_hook(mlx.window, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(mlx.window, 3, (1L << 1), key_released, (void *)0);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	mlx_loop_hook(mlx.pointer, update, (void *)0);
	mlx_loop(mlx.pointer);
	return 0;
}
