/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 01:59:36 by keddib            #+#    #+#             */
/*   Updated: 2020/11/02 02:43:01 by keddib           ###   ########.fr       */
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

	next_half = all->win.half_win + (all->win.look * 5);
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
	if (!is_this_wall(new_player_x, new_player_y, all))
	{
		all->fpp.x = new_player_x;
		all->fpp.y = new_player_y;
	}
}

int		is_this_wall(float x, float y, t_all *all)
{
	int index_x;
	int index_y;

	if (x < 0 || x > (all->win.rows * TILE_SIZE) ||
			y < 0 || y > (all->win.cols * TILE_SIZE))
		return (1);
	index_x = floor(x / TILE_SIZE);
	index_y = floor(y / TILE_SIZE);
	if (index_y >= all->win.cols || index_x >= all->win.rows)
		return (1);
	if (all->win.array[index_y][index_x] == '1')
		return (1);
	return (0);
}

int		ft_puterror(char *error)
{
	char *e;

	e = "\033[1;31m(x) Error\n >> \033[0;31m";
	write(1, e, ft_strlen(e));
	write(1, error, ft_strlen(error));
	return (0);
}

int		ft_exit(int i, t_all *all)
{
	int i;

	i = 0;
	if (i == 0)
	{
		ft_free(all->win.array, all->win.cols);
		mlx_destroy_image(all->mlx.pointer, all->mlx.image);
		mlx_destroy_window(all->mlx.pointer, all->mlx.window);
		// free(all->ray);
		while (i < 4)
			free(all->tex.data[i++]);
	}
	else if (i == 1)
		ft_puterror("ERROR\nFILE NOT FOUND\n");
	else if (i == 2)
		ft_puterror("Somthing is Missing Check Your File\n");
	else if (i == 3)
		ft_putstr("ERROR\nDUPP PLAYER\n");
	exit(0);
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
