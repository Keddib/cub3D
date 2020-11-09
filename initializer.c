/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 06:19:46 by keddib            #+#    #+#             */
/*   Updated: 2020/11/09 06:24:45 by keddib           ###   ########.fr       */
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
	all->win.look = 0;
	if (!(all->ray = malloc(sizeof(t_ray) * all->win.width)))
		ft_exit(1, all);
}
