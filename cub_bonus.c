/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:27:59 by keddib            #+#    #+#             */
/*   Updated: 2020/11/11 23:50:25 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initilaize_obj(t_bonus *obj, t_all *all)
{
	obj->factor = (all->win.width * 0.4);
	obj->start_x = (all->win.width / 2) - (obj->factor / 2);
	obj->end_x = (all->win.width / 2) + (obj->factor / 2);
	obj->start_y = all->win.height - obj->factor;
	obj->end_y = all->win.height;
}

void	life_bar(t_bonus obj, t_all *all)
{
	int ty;
	int tx;
	int color;

	obj.factor = (all->win.width * 0.3);
	obj.start_y = 5;
	ty = 0;
	while (obj.start_y < (obj.factor * 0.3) + 5)
	{
		tx = 0;
		obj.offy = ty * (float)(all->tex.height / (obj.factor * 0.3));
		obj.start_x = 5;
		while (obj.start_x < obj.factor + 5)
		{
			obj.offx = tx * (float)(all->tex.width / obj.factor);
			color = all->tex.data[6][(all->tex.width * obj.offy) + obj.offx];
			if (color != 0x00)
				my_mlx_pixel_put(all, obj.start_x, obj.start_y, color);
			tx++;
			obj.start_x++;
		}
		ty++;
		obj.start_y++;
	}
}

void	hold_weapon(t_all *all)
{
	t_bonus obj;
	int		color;
	int		ty;
	int		tx;

	initilaize_obj(&obj, all);
	ty = 0;
	while (obj.start_y++ < all->win.height)
	{
		tx = 0;
		obj.offy = ty * (float)(64 / obj.factor);
		obj.start_x = (all->win.width / 2) - (obj.factor / 2);
		while (obj.start_x++ < (all->win.width / 2) + (obj.factor / 2))
		{
			obj.offx = tx * (float)(64 / obj.factor);
			color = all->tex.data[5][(TILE_SIZE * obj.offy) + obj.offx];
			if (color != 0xffffff)
				my_mlx_pixel_put(all, obj.start_x, obj.start_y, color);
			tx++;
		}
		ty++;
	}
	life_bar(obj, all);
}
