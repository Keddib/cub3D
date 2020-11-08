/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/11/03 01:12:42 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char *dst;
	int newy;
	int index;
	dst = all->mlx.addr + (y * all->mlx.line_length + x *
		(all->mlx.bits_per_pixel / 8));
	if (x < all->win.width && x >= 0 && y < all->win.height && y >= 0)
	{
		if (all->save == 1)
		{
			int_to_rgb(all, color);
			newy = all->win.height - (y+1);
			index = newy * g_bmp.row_bytes + x * 3;
			g_bmp.buffer[index + 0] = all->rgb.b;
			g_bmp.buffer[index + 1] = all->rgb.g;
			g_bmp.buffer[index + 2] = all->rgb.r;
		}
		*(unsigned int *)dst = color;
	}
}

int setup(t_all *all)
{
	all->mlx.pointer = mlx_init();
	read_file(argv[1], &all);
	load_images(&all);
	find_sprite(&all);
	if (all->save == 1)
		create_bmp(&all);
	all->save = 0;
	all->win.proj_plane = (all->win.width / 2) / tan(FOV_ANGLE / 2);
	all->win.half_win = (all->win.height / 2);
	all->win.look = 0;
}

int update(t_all *all)
{
	update_player(all);
	cast_all_rays(all);
	render_3d_projection(all);
	ft_sprites(all);
	if (all->save == 1)
		save_bmp(all);
	mlx_put_image_to_window(
		all->mlx.pointer,
		all->mlx.window,
		all->mlx.image, 0, 0);
	return 0;
}

int ft_close(t_all *all)
{
	ft_exit(0, all);
	return 0;
}

int main(int argc, char **argv)
{
	t_all all;
	if (argc != 2)
		ft_exit(2, &all);
	all.mlx.window = mlx_new_window(
		all.mlx.pointer,
		all.win.width,
		all.win.height,
		"Cub3d");
	if (!(all.ray = malloc(sizeof(t_ray) * all.win.width)))
		ft_exit(1, &all);
	all.mlx.image = mlx_new_image(all.mlx.pointer, all.win.width, all.win.height);
	all.mlx.addr = mlx_get_data_addr(all.mlx.image, &all.mlx.bits_per_pixel, &all.mlx.line_length, &all.mlx.endian);
	mlx_loop_hook(all.mlx.pointer, update, &all);
	mlx_hook(all.mlx.window, 2, 1L << 0, key_pressed, &all);
	mlx_hook(all.mlx.window, 3, (1L << 1), key_released, &all);
	mlx_hook(all.mlx.window, 17, 0, ft_close, &all);
	mlx_loop(all.mlx.pointer);
	return 0;
}
