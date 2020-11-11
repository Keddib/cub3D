/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 00:40:01 by keddib            #+#    #+#             */
/*   Updated: 2020/11/10 00:02:51 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_pressed(int key, t_all *all)
{
	if (key == 65307)
		ft_exit(0, all);
	if (key == 119)
		all->fpp.walk_direction = +1;
	else if (key == 115)
		all->fpp.walk_direction = -1;
	else if (key == 100)
		all->fpp.side_direction = +1;
	else if (key == 97)
		all->fpp.side_direction = -1;
	else if (key == 65363)
		all->fpp.turn_direction = +1;
	else if (key == 65361)
		all->fpp.turn_direction = -1;
	else if (key == 65364)
		all->win.look = 1;
	else if (key == 65362)
		all->win.look = -1;
	return (0);
}

int		key_released(int key, t_all *all)
{
	if (key == 119|| key == 115)
		all->fpp.walk_direction = 0;
	else if (key == 100 || key == 97)
		all->fpp.side_direction = 0;
	else if (key == 65361 || key == 65363)
		all->fpp.turn_direction = 0;
	else if (key == 65364)
		all->win.look = 0;
	else if (key == 65362)
		all->win.look = 0;
	return (0);
}

int		ft_close(t_all *all)
{
	ft_exit(0, all);
	return (0);
}
