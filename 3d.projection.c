/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:53:14 by keddib            #+#    #+#             */
/*   Updated: 2020/11/02 00:52:36 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void render_walls(t_all *all, int i, int ws_height)
{
    int start;
    unsigned int color;
    int offx;
    int offy;

    start = all->ray[i].wall_top;
    if (all->ray[i].was_hit_vertical)
        offx = (int)all->ray[i].wall_hit_y % TILE_SIZE;
    else
        offx = (int)all->ray[i].wall_hit_x % TILE_SIZE;
    int wich_tex = 0;
    if (all->ray[i].was_hit_vertical && all->ray[i].ray_facingright)
        wich_tex = 3;
    else if (all->ray[i].was_hit_vertical && all->ray[i].ray_facingleft)
        wich_tex = 2;
    else if (all->ray[i].was_hit_vertical == 0 && all->ray[i].ray_facingdown)
        wich_tex = 1;
    while (start < all->ray[i].wall_bottom)
    {
        offy = (start - (all->win.half_win - (ws_height / 2))) * ((float)TILE_SIZE / ws_height);
        color = all->tex.data[wich_tex][(TILE_SIZE * offy) + offx];
        my_mlx_pixel_put(all, i, start++, color);
    }
    start = 0;
    while (start < all->ray[i].wall_top)
        my_mlx_pixel_put(all, i, start++, all->tex.ciel);
    start = all->ray[i].wall_bottom;
    while (start < all->win.height)
        my_mlx_pixel_put(all, i, start++, all->tex.floor);
}

void render_3d_projection(t_all *all)
{
    int wall_stripe_hieght;
    float correct_distance;
    for (int i = 0; i < all->win.width; i++)
    {
        correct_distance =
            all->ray[i].distance * cos(all->ray[i].ray_angle - all->fpp.rotation_angle);
        wall_stripe_hieght = (int)((TILE_SIZE / correct_distance) * all->win.proj_plane);
        all->ray[i].wall_top = all->win.half_win - (wall_stripe_hieght / 2);
        if (all->ray[i].wall_top < 0)
            all->ray[i].wall_top = 0;
        all->ray[i].wall_bottom = all->win.half_win + (wall_stripe_hieght / 2);
        if (all->ray[i].wall_bottom > all->win.height)
            all->ray[i].wall_bottom = all->win.height;
        render_walls(all, i, wall_stripe_hieght);
    }
}