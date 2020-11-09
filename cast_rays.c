/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:25:11 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 04:56:19 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

float	normlize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_ray(float ray_angle, t_all *all, int i)
{
	all->ray[i].ray_angle = normlize_angle(ray_angle);
	all->ray[i].facingdown =
		(all->ray[i].ray_angle > 0 && all->ray[i].ray_angle < PI);
	all->ray[i].facingup = !all->ray[i].facingdown;
	all->ray[i].facingright =
		all->ray[i].ray_angle < 0.5 * PI || all->ray[i].ray_angle > 1.5 * PI;
	all->ray[i].facingleft = !all->ray[i].facingright;
	get_horizontal(all, i);
	get_vertical(all, i);
	calc_distances(all);
	if (all->incept.vert_distance < all->incept.horz_distance)
	{
		all->ray[i].distance = all->incept.vert_distance;
		all->ray[i].wall_hit_x = all->incept.vert_x;
		all->ray[i].wall_hit_y = all->incept.vert_y;
		all->ray[i].was_hit_vertical = 1;
	}
	else
	{
		all->ray[i].distance = all->incept.horz_distance;
		all->ray[i].wall_hit_x = all->incept.horz_x;
		all->ray[i].wall_hit_y = all->incept.horz_y;
		all->ray[i].was_hit_vertical = 0;
	}
}

void	cast_all_rays(t_all *all)
{
	int		i;
	int		num_rays;
	float	ray_angle;

	i = 0;
	num_rays = all->win.width;
	while (i < num_rays)
	{
		ray_angle = all->fpp.rotation_angle +
				atan((i - num_rays / 2) / all->win.proj_plane);
		cast_ray(ray_angle, all, i);
		i++;
	}
}
