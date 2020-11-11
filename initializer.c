/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 06:19:46 by keddib            #+#    #+#             */
/*   Updated: 2020/11/11 05:16:22 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initializer_one(t_all *all)
{
	int i;

	i = 0;
	all->file.counter = 0;
	all->file.map_found = 0;
	all->win.chr = 0;
	all->win.rows = 0;
	all->num_sprt = 0;
	all->tex.color[0] = 0;
	all->tex.color[1] = 0;
	while (i < 5)
		all->tex.file[i++] = NULL;
}

void	initializer_two(t_all *all)
{
	all->win.proj_plane = (all->win.width / 2) / tan(FOV_ANGLE / 2);
	all->win.half_win = (all->win.height / 2);
	g_half_win = (all->win.height / 2);
	all->win.look = 0;
	if (!(all->ray = malloc(sizeof(t_ray) * all->win.width)))
		ft_exit(1, all);
}

void	init_errors(void)
{
	g_messages[0] = "Invalid file name!\n";
	g_messages[1] = "Added info in an element\n";
	g_messages[2] = "Duplicate Texture\n";
	g_messages[3] = "Duplicate Color\n";
	g_messages[4] = "Error in Resolution\n";
	g_messages[5] = "Stop Idiot! You have reached the range of g_screen\n";
	g_messages[6] = "Invalid Map\n";
	g_messages[7] = "NO SUCH FILE OR DIRECTORY\n";
	g_messages[8] = "Allocation Failed\n";
	g_messages[9] = "STOP! you need XPM file\n";
	g_messages[10] = "INVALID MAP LINE\n";
	g_messages[11] = "NO PLAYER FOUNDED\n";
	g_messages[12] = "NEW LINE IN MAP\n";
	g_messages[13] = "DUPLICATE_PLAYER\n";
	g_messages[14] = "INVALID CHARCATER\n";
	g_messages[15] = "INVALID COLORS\n";
	g_messages[16] = "DUPLICATE_SPRITE\n";
	g_messages[17] = "ARGUMENTS ARE MORE OR LESS\n";
	g_messages[18] = "ARE YOU KIDDING ME IF YOU WANNA PLAY FIX RESOLUTION\n";
}

float	s_distance_to_fpp(t_all *all, float x, float y)
{
	float dx;
	float dy;

	dx = all->fpp.x - x;
	dy = all->fpp.y - y;
	return (sqrtf(powf(dx, 2) + powf(dy, 2)));
}

int		sprite_color(t_all *all, t_sprite sprite, int i, int j)
{
	int color;

	color = all->tex.data[4][(unsigned int)(64 *
				(64 * j / (int)(sprite.size)) +
					(64 * i / (int)sprite.size))];
	return (color);
}
