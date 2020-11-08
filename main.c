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
	dst = all->mlx.addr + (y * g_mlx.line_n + x *
		(g_mlx.bpp / 8));
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

// int setup(t_all *all)
// {

// 	return 0;
// }

int update(t_all *all)
{
	update_player(all);
	cast_all_rays(all);
	render_3d_projection(all);
	ft_sprites(all);
	if (all->save == 1)
		save_bmp(all);
	mlx_put_image_to_window(
		g_mlx.ptr,
		g_mlx.win,
		g_mlx.img, 0, 0);
	return 0;
}

int ft_close(t_all *all)
{
	ft_exit(0, all);
	return 0;
}

void check_arguments(t_all *all)
{
	int i;
	int j;
	char *cub;

	i = 0;
	j = 0;
	cub = "buc.";
	if (all->param2)
	{
		if (ft_strcmp("--save", all->param2) == 0)
			all->save = 1;
		else
			ft_exit(1, all);
	}
	if (!all->param1 || strlen(all->param1) <= 4)
		ft_exit(1, all);
	while (all->param1[i])
		i++;
	i -= 1;
	while (cub[j])
	{
		if(all->param1[i] == cub[j])
			i--;
		else
			ft_exit(1, all);
		j++;
	}
}

int main(int argc, char **argv)
{
	t_all all;
	g_mlx.ptr = mlx_init();
	if (argc == 2)
		all.param1 = argv[1];
	else if(argc == 3)
	{
		all.param1 = argv[1];
		all.param2 = argv[2];
	}
	else
		ft_exit(2, &all);
	check_arguments(&all);
	read_file(all.param1, &all);
	load_images(&all);
	find_sprite(&all);
	if (all.save == 1)
		create_bmp(&all);
	all.win.proj_plane = (all.win.width / 2) / tan(FOV_ANGLE / 2);
	all.win.half_win = (all.win.height / 2);
	all.win.look = 0;
	g_mlx.win = mlx_new_window(
		g_mlx.ptr,
		all.win.width,
		all.win.height,
		"Cub3d");
	if (!(all.ray = malloc(sizeof(t_ray) * all.win.width)))
		ft_exit(1, &all);
	g_mlx.img = mlx_new_image(g_mlx.ptr, all.win.width, all.win.height);
	all.mlx.addr = mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, &g_mlx.line_n, &g_mlx.endian);
	mlx_loop_hook(g_mlx.ptr, update, &all);
	mlx_hook(g_mlx.win, 2, 1L << 0, key_pressed, &all);
	mlx_hook(g_mlx.win, 3, (1L << 1), key_released, &all);
	mlx_hook(g_mlx.win, 17, 0, ft_close, &all);
	mlx_loop(g_mlx.ptr);
	return 0;
}
