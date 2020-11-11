/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 21:49:36 by keddib            #+#    #+#             */
/*   Updated: 2020/11/10 01:56:44 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		update(t_all *all)
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
	// mlx_destroy_image(g_mlx.ptr, g_mlx.img);
	return (0);
}

int		setup(t_all *all)
{
	g_mlx.ptr = mlx_init();
	check_arguments(all);
	initializer_one(all);
	read_file(all->param1, all);
	initializer_two(all);
	load_images(all);
	find_sprite(all);
	if (all->save == 1)
	{
		create_bmp(all);
		update(all);
	}
	else{
		g_mlx.win = mlx_new_window(
			g_mlx.ptr,
			all->win.width,
			all->win.height,
			"Cub3d");
		g_mlx.img = mlx_new_image(g_mlx.ptr, all->win.width, all->win.height);
		g_mlx.addr =
		mlx_get_data_addr(g_mlx.img, &g_mlx.bpp, &g_mlx.line_n, &g_mlx.endian);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_all all;

	init_errors();
	if (argc == 2)
		all.param1 = argv[1];
	else if (argc == 3)
	{
		all.param1 = argv[1];
		all.param2 = argv[2];
	}
	else
		ft_exit(17, &all);
	setup(&all);
	mlx_loop_hook(g_mlx.ptr, update, &all);
	mlx_hook(g_mlx.win, 2, 1L << 0, key_pressed, &all);
	mlx_hook(g_mlx.win, 3, (1L << 1), key_released, &all);
	mlx_hook(g_mlx.win, 17, 0, ft_close, &all);
	mlx_loop(g_mlx.ptr);
	return (0);
}
