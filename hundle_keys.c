/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 00:40:01 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 05:21:37 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_pressed(int key, t_all *all)
{
	if (key == 53)
		ft_exit(0, all);
	if (key == 13)
		all->fpp.walk_direction = +1;
	else if (key == 1)
		all->fpp.walk_direction = -1;
	else if (key == 2)
		all->fpp.side_direction = +1;
	else if (key == 0)
		all->fpp.side_direction = -1;
	else if (key == 124)
		all->fpp.turn_direction = +1;
	else if (key == 123)
		all->fpp.turn_direction = -1;
	else if (key == 126)
		all->win.look = 1;
	else if (key == 125)
		all->win.look = -1;
	return (0);
}

int		key_released(int key, t_all *all)
{
	if (key == 13 || key == 1)
		all->fpp.walk_direction = 0;
	else if (key == 2 || key == 0)
		all->fpp.side_direction = 0;
	else if (key == 124 || key == 123)
		all->fpp.turn_direction = 0;
	else if (key == 126)
		all->win.look = 0;
	else if (key == 125)
		all->win.look = 0;
	return (0);
}

float	s_distance_to_fpp(t_all *all, float x, float y)
{
	float dx;
	float dy;

	dx = all->fpp.x - x;
	dy = all->fpp.y - y;
	return (sqrtf(powf(dx, 2) + powf(dy, 2)));
}
