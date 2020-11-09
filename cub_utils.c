/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:59:36 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 04:56:33 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	update_player(t_all *all)
{
	float new_player_x;
	float new_player_y;
	float move_step;
	float side_step;
	float nex_half;

	nex_half = all->win.half_win + (all->win.look * 5);
	if (nex_half > (all->win.height / 4) &&
			nex_half < ((all->win.height / 4) * 3))
		all->win.half_win += (all->win.look * 5);
	all->fpp.rotation_angle += all->fpp.turn_direction * TURN_SPEED;
	move_step = all->fpp.walk_direction * WALK_SPEED;
	new_player_x = all->fpp.x + cos(all->fpp.rotation_angle) * move_step;
	new_player_y = all->fpp.y + sin(all->fpp.rotation_angle) * move_step;
	side_step = all->fpp.side_direction * WALK_SPEED;
	new_player_x += cos(all->fpp.rotation_angle + (90 * RADIUN)) * side_step;
	new_player_y += sin(all->fpp.rotation_angle + (90 * RADIUN)) * side_step;
	if (!is_this_wall(new_player_x, new_player_y, all, 0))
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
		if (all->win.array[index_y][index_x] == '1')
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

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*z;

	s = (unsigned char *)s1;
	z = (unsigned char *)s2;
	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s[i] != '\0' || z[i] != '\0')
	{
		if (s[i] - z[i] != 0)
			return (s[i] - z[i]);
		i++;
	}
	return (*s1 - *s2);
}
