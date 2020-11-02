/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incept.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:11:43 by keddib            #+#    #+#             */
/*   Updated: 2020/11/02 02:12:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	calc_distances(t_all *all)
{
	all->incept.horz_distance = all->incept.is_horz_hit ?
		distance_between_points(
				all->fpp.x, all->fpp.y,
				all->incept.horz_x,
				all->incept.horz_y)
		: (float)INT_MAX;
	all->incept.vert_distance = all->incept.is_vert_hit ?
		distance_between_points(
				all->fpp.x,
				all->fpp.y,
				all->incept.vert_x,
				all->incept.vert_y)
		: (float)INT_MAX;
}

void	h_until_wall(float n_x, float n_y, t_all *all, int i)
{
	while (n_x >= 0 && n_x <= (TILE_SIZE * all->win.rows) &&
			n_y >= 0 && n_y <= (TILE_SIZE * all->win.cols))
	{
		all->incept.check_x = n_x;
		all->incept.check_y = n_y + (all->ray[i].ray_facingup ? -1 : 0);
		if (is_this_wall(all->incept.check_x, all->incept.check_y, all))
		{
			all->incept.horz_x = n_x;
			all->incept.horz_y = n_y;
			all->incept.is_horz_hit = 1;
			break ;
		}
		else
		{
			n_x += all->incept.xstep;
			n_y += all->incept.ystep;
		}
	}
}

void	v_until_wall(float x, float y, t_all *all, int i)
{
	while (x >= 0 && x <= (TILE_SIZE * all->win.rows) &&
			y >= 0 && y <= (TILE_SIZE * all->win.cols))
	{
		all->incept.check_x = x + (all->ray[i].ray_facingleft ? -1 : 0);
		all->incept.check_y = y;
		if (is_this_wall(all->incept.check_x, all->incept.check_y, all))
		{
			all->incept.vert_x = x;
			all->incept.vert_y = y;
			all->incept.is_vert_hit = 1;
			break ;
		}
		else
		{
			x += all->incept.xstep;
			y += all->incept.ystep;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*   Find the y-coordinate of the closest horizontal grid intersection        */
/*   Find the x-coordinate of the closest horizontal grid intersection        */
/*   Calculate the increment all->incept.xstep and all->incept.ystep          */
/*   Increment all->incept.xstep and all->incept.ystep until we find a wall   */
/*                                                                            */
/* ************************************************************************** */

void	get_horizontal(t_all *all, int i)
{
	float next_x;
	float next_y;

	all->incept.is_horz_hit = 0;
	all->incept.horz_x = 0;
	all->incept.horz_y = 0;
	all->incept.yintercept = floor(all->fpp.y / TILE_SIZE) *
		TILE_SIZE;
	all->incept.yintercept += all->ray[i].ray_facingdown ? TILE_SIZE : 0;
	all->incept.xintercept = all->fpp.x +
		(all->incept.yintercept - all->fpp.y) /
		tan(all->ray[i].ray_angle);
	all->incept.ystep = TILE_SIZE;
	all->incept.ystep *= all->ray[i].ray_facingup ? -1 : 1;
	all->incept.xstep = TILE_SIZE / tan(all->ray[i].ray_angle);
	all->incept.xstep *=
		(all->ray[i].ray_facingleft && all->incept.xstep > 0) ? -1 : 1;
	all->incept.xstep *=
		(all->ray[i].ray_facingright && all->incept.xstep < 0) ? -1 : 1;
	next_x = all->incept.xintercept;
	next_y = all->incept.yintercept;
	h_until_wall(next_x, next_y, all, i);
}

/******************************************************************************/
/*                                                                            */
/*    Find the x-coordinate of the closest vertical grid intersection         */
/*    Find the y-coordinate of the closest vertical grid intersection		  */
/*    Calculate the increment all->incept.xstep and all->incept.ystep		  */
/*    Increment all->incept.xstep and all->incept.ystep until we find a wall  */
/*                                                                            */
/******************************************************************************/

void	get_vertical(t_all *all, int i)
{
	float next_x;
	float next_y;

	all->incept.is_vert_hit = 0;
	all->incept.vert_x = 0;
	all->incept.vert_y = 0;
	all->incept.xintercept = floor(all->fpp.x / TILE_SIZE) *
		TILE_SIZE;
	all->incept.xintercept += all->ray[i].ray_facingright ?
		TILE_SIZE : 0;
	all->incept.yintercept = all->fpp.y +
		(all->incept.xintercept - all->fpp.x) *
		tan(all->ray[i].ray_angle);
	all->incept.xstep = TILE_SIZE;
	all->incept.xstep *= all->ray[i].ray_facingleft ? -1 : 1;
	all->incept.ystep = TILE_SIZE * tan(all->ray[i].ray_angle);
	all->incept.ystep *=
		(all->ray[i].ray_facingup && all->incept.ystep > 0) ? -1 : 1;
	all->incept.ystep *=
		(all->ray[i].ray_facingdown && all->incept.ystep < 0) ? -1 : 1;
	next_x = all->incept.xintercept;
	next_y = all->incept.yintercept;
	v_until_wall(next_x, next_y, all, i);
}
