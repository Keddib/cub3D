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

int		ft_close(t_all *all)
{
	ft_exit(0, all);
	return (0);
}
