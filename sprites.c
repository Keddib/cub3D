/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 04:17:58 by keddib            #+#    #+#             */
/*   Updated: 2020/11/03 04:40:12 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	normalize_sprite_ang(t_all *all, float rot_angle, int i)
{
	while (all->sprite[i].angle - rot_angle > M_PI)
       		all->sprite[i].angle -= 2 * M_PI;
    	while (all->sprite[i].angle - rot_angle < -M_PI)
        	all->sprite[i].angle += 2 * M_PI;
}

float 	s_distance_to_fpp(t_all *all, float x, float y)
{
	float dx;
	float dy;

	dx = all->fpp.x - x;
	dy = all->fpp.y - y;
	return (sqrtf(powf(dx, 2) + powf(dy, 2)));
}

void	sort_sprite(t_all *all)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = -1;
	while (++i < all->num_sprt)
	{
		j = i;
		while (++j < all->num_sprt)
		{
			if (all->sprite[i].distance < all->sprite[j].distance)
			{
				temp = all->sprite[i];
				all->sprite[i] = all->sprite[j];
				all->sprite[j] = temp;
			}
		}
	}
}

void	draw_sprite(t_all *all, t_sprite sprite)
{
	int		i;
	int		j;
	unsigned int		color;
	float	factor;


	i = -1;
	factor = 64 / sprite.size;
	while (++i < (int)sprite.size)
	{
		if (sprite.offx + i < 0 || sprite.offx + i > all->win.width)
			continue ;
		if ((int)(sprite.offx + i - 1) < all->win.width && (int)(sprite.offx + i - 1) >= 0)
			if (all->ray[(int)(sprite.offx + i - 1)].distance <= sprite.distance)
				continue ;
		j = -1;
		while (++j < (int)sprite.size)
		{
			if (sprite.offy + j < 0 || sprite.offy + j > all->win.height)
				continue ;
			color = all->tex.data[4][(unsigned int)(all->tex.width * (all->tex.height * j / (int)(sprite.size)) + (all->tex.width * i / (int)sprite.size))];
			if (color != all->tex.data[4][0])
				my_mlx_pixel_put(all, ((int)sprite.offx + i), ((int)sprite.offy + j), color);
		}
	}
}


void	ft_sprites(t_all *all)
{
	int		i;
	float	rot_angle;

	sort_sprite(all);
	rot_angle = normlize_angle(all->fpp.rotation_angle);
	i = 0;
	while (i < all->num_sprt)
	{
		all->sprite[i].distance = (int)s_distance_to_fpp(all, all->sprite[i].x, all->sprite[i].y);
		all->sprite[i].angle =  atan2f(all->sprite[i].y - all->fpp.y, all->sprite[i].x - all->fpp.x);
		normalize_sprite_ang(all, rot_angle, i);
			all->sprite[i].size = all->win.width / all->sprite[i].distance * (float)TILE_SIZE;
		all->sprite[i].offx = (((all->sprite[i].angle) - (rot_angle))
								* all->win.width / (60 * RADIUN)
								+ (all->win.width / 2 - all->sprite[i].size / 2));
		all->sprite[i].offy = (all->win.half_win - all->sprite[i].size / 2);
		draw_sprite(all, all->sprite[i]);
		i++;
	}

}

void find_sprite(t_all *all)
{
    int i;
    int j;
    int x;

    i = 0;
    j = 0;
    x = 0;
    if (!(all->sprite = malloc(sizeof(t_sprite) * all->num_sprt)))
		ft_exit(1, all);
    while (all->win.array[j])
    {
        i = 0;
        while (all->win.array[j][i])
        {
            if (all->win.array[j][i] == '2')
            {
                all->sprite[x].x = (i * TILE_SIZE) + (TILE_SIZE / 2);
                all->sprite[x].y = (j * TILE_SIZE) + (TILE_SIZE / 2);
                x++;
            }
            i++;
        }
        j++;
    }
}

