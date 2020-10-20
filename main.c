/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/10/20 11:26:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void render_walls(t_ray *ray, int i, int ws_height)
{
	int start;
	unsigned int color;
	int offx;
	int offy;

	start = ray[i].wall_top;

	if (ray[i].was_hit_vertical)
		offx = (int)ray[i].wall_hit_y % TILE_SIZE;
	else
		offx = (int)ray[i].wall_hit_x % TILE_SIZE;

	while (start < ray[i].wall_bottom)
	{
		offy = (start - ((window.height / 2) - (ws_height / 2))) * ((float)TILE_SIZE / ws_height);
		color = tex[(TILE_SIZE * offy) + offx];
		// color = ray[i].was_hit_vertical ? 0xd3d3d3 : 0xffffff;
		my_mlx_pixel_put(&mlx, i, start++, color);
	}
	start = 0;
	while (start < ray[i].wall_top)
		my_mlx_pixel_put(&mlx, i, start++, 0x5cabf4);
	start = ray[i].wall_bottom;
	while (start < window.height)
		my_mlx_pixel_put(&mlx, i, start++, 0xc58b00);
}

void render_3d_projection(t_ray *rays)
{
	int i;
	int wall_stripe_hieght;
	float correct_distance;
	float distance_proj_plane;

	i = 0;
	while (i < window.width)
	{
		correct_distance =
			rays[i].distance * cos(rays[i].ray_angle - player.rotation_angle);
		distance_proj_plane = (window.width / 2) / tan(FOV_ANGLE / 2);
		wall_stripe_hieght = (int)((TILE_SIZE / correct_distance) * distance_proj_plane);
		rays[i].wall_top = (window.height / 2) - (wall_stripe_hieght / 2);
		if (rays[i].wall_top < 0)
			rays[i].wall_top = 0;
		rays[i].wall_bottom = (window.height / 2) + (wall_stripe_hieght / 2);
		if (rays[i].wall_bottom > window.height)
			rays[i].wall_bottom = window.height;
		render_walls(rays, i++, wall_stripe_hieght);
	}
}

int update(void *param)
{
	t_ray *rays;
	mlx_destroy_image(mlx.pointer, mlx.image);
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_new_image(mlx.pointer, window.width, window.height);
	// map_render();
	// render_player(player.x, player.y);
	update_player();
	rays = cast_all_rays();
	// for (int i = 0; i < window.width; i++)
	// {
	// 	render_ray(&rays[i]);
	// }
	render_3d_projection(rays);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	free(rays);
	return 0;
}

int main()
{
	mlx.pointer = mlx_init();
	read_file("map.cub");
	tex = load_images();
	mlx.window = mlx_new_window(mlx.pointer, window.width, window.height, "Cub3d");
	mlx.image = mlx_new_image(mlx.pointer, window.width, window.height);
	mlx.addr = mlx_get_data_addr(mlx.image, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	mlx_hook(mlx.window, 2, 1L << 0, key_pressed, (void *)0);
	mlx_hook(mlx.window, 3, (1L << 1), key_released, (void *)0);
	mlx_put_image_to_window(mlx.pointer, mlx.window, mlx.image, 0, 0);
	mlx_loop_hook(mlx.pointer, update, (void *)0);
	mlx_loop(mlx.pointer);
	return 0;
}