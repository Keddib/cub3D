/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projaction_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:53:14 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 04:56:08 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		which_texture(t_all *all, int x)
{
	int wich_tex;

	wich_tex = 0;
	if (all->ray[x].was_hit_vertical && all->ray[x].facingright)
		wich_tex = 3;
	else if (all->ray[x].was_hit_vertical && all->ray[x].facingleft)
		wich_tex = 2;
	else if (all->ray[x].was_hit_vertical == 0 && all->ray[x].facingdown)
		wich_tex = 1;
	return (wich_tex);
}

void	calculate_walls(t_all *all, int x, int ws_height)
{
	int				start;
	unsigned int	color;
	int				offx;
	int				offy;
	int				wich_tex;

	wich_tex = which_texture(all, x);
	start = all->ray[x].wall_top;
	if (all->ray[x].was_hit_vertical)
		offx = (int)all->ray[x].wall_hit_y % TILE_SIZE;
	else
		offx = (int)all->ray[x].wall_hit_x % TILE_SIZE;
	while (start < all->ray[x].wall_bottom)
	{
		offy = (start - (all->win.half_win - (ws_height / 2))) *
			((float)TILE_SIZE / ws_height);
		color = all->tex.data[wich_tex][(TILE_SIZE * offy) + offx];
		my_mlx_pixel_put(all, x, start++, color);
	}
	start = 0;
	while (start < all->ray[x].wall_top)
		my_mlx_pixel_put(all, x, start++, all->tex.color[0]);
	start = all->ray[x].wall_bottom;
	while (start < all->win.height)
		my_mlx_pixel_put(all, x, start++, all->tex.color[1]);
}

void	render_3d_projection(t_all *all)
{
	int			wall_stripe_hieght;
	int			x;
	float		correct_distance;

	x = 0;
	while (x < all->win.width)
	{
		correct_distance =
			all->ray[x].distance *
			cos(all->ray[x].ray_angle - all->fpp.rotation_angle);
		wall_stripe_hieght = (int)((TILE_SIZE / correct_distance) *
				all->win.proj_plane);
		all->ray[x].wall_top = all->win.half_win - (wall_stripe_hieght / 2);
		if (all->ray[x].wall_top < 0)
			all->ray[x].wall_top = 0;
		all->ray[x].wall_bottom = all->win.half_win + (wall_stripe_hieght / 2);
		if (all->ray[x].wall_bottom > all->win.height)
			all->ray[x].wall_bottom = all->win.height;
		calculate_walls(all, x, wall_stripe_hieght);
		x++;
	}
}
