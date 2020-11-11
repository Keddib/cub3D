/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cub_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:59:36 by keddib            #+#    #+#             */
/*   Updated: 2020/11/11 05:59:01 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_bonus(t_all *all, float new_px, float new_py)
{
	all->win.half_win = g_half_win;
	if (!is_this_wall(new_px, new_py, all, 0))
	{
		all->fpp.x = new_px;
		all->fpp.y = new_py;
	}
}

void	update_player(t_all *all)
{
	float new_player_x;
	float new_player_y;
	float move_step;
	float side_step;
	float nex_half;

	nex_half = g_half_win + (all->win.look * 5);
	if (nex_half > (all->win.height / 4) &&
			nex_half < ((all->win.height / 4) * 3))
		g_half_win += (all->win.look * 5);
	all->fpp.rotation_angle += all->fpp.turn_direction * TURN_SPEED;
	move_step = all->fpp.walk_direction * WALK_SPEED;
	new_player_x = all->fpp.x + cos(all->fpp.rotation_angle) * move_step;
	new_player_y = all->fpp.y + sin(all->fpp.rotation_angle) * move_step;
	side_step = all->fpp.side_direction * WALK_SPEED;
	new_player_x += cos(all->fpp.rotation_angle + (90 * RADIUN)) * side_step;
	new_player_y += sin(all->fpp.rotation_angle + (90 * RADIUN)) * side_step;
	if (BONUS == 1)
		update_bonus(all, new_player_x, new_player_y);
	else
	{
		all->fpp.x = new_player_x;
		all->fpp.y = new_player_y;
	}
}

int		is_this_wall(float x, float y, t_all *all, int q)
{
	int index_x;
	int index_y;

	index_x = floor(x / TILE_SIZE);
	index_y = floor(y / TILE_SIZE);
	if (index_y >= all->win.cols || index_y < 0)
		return (1);
	if (index_x < 0 || (size_t)index_x >= ft_strlen(all->win.array[index_y]))
		return (1);
	if (q == 1)
	{
		if (all->win.array[index_y][index_x] == '1' ||
		all->win.array[index_y][index_x] == '4')
			return (1);
	}
	else
	{
		if (all->win.array[index_y][index_x] == '1' ||
		all->win.array[index_y][index_x] == '2')
			return (1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;
	int		newy;
	int		index;

	dst = g_mlx.addr + (y * g_mlx.line_n + x * (g_mlx.bpp / 8));
	if (x < all->win.width && x >= 0 && y < all->win.height && y >= 0)
	{
		if (all->save == 1)
		{
			int_to_rgb(all, color);
			newy = all->win.height - (y + 1);
			index = newy * g_bmp.row_bytes + x * 3;
			g_bmp.buffer[index + 0] = all->rgb.b;
			g_bmp.buffer[index + 1] = all->rgb.g;
			g_bmp.buffer[index + 2] = all->rgb.r;
		}
		*(unsigned int *)dst = color;
	}
}
