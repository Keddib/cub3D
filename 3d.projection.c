/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:53:14 by keddib            #+#    #+#             */
/*   Updated: 2020/10/25 00:26:07 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void render_walls(t_ray ray, int i, int ws_height, t_texture *tex)
{
    int start;
    unsigned int color;
    int offx;
    int offy;

    start = ray.wall_top;
    if (ray.was_hit_vertical)
        offx = (int)ray.wall_hit_y % TILE_SIZE;
    else
        offx = (int)ray.wall_hit_x % TILE_SIZE;
    int wich_tex = 0;
    if (ray.was_hit_vertical && ray.ray_facingright)
        wich_tex = 3;
    else if (ray.was_hit_vertical && ray.ray_facingleft)
        wich_tex = 2;
    else if (ray.was_hit_vertical == 0 && ray.ray_facingdown)
        wich_tex = 1;
    while (start < ray.wall_bottom)
    {
        offy = (start - ((g_window.height / 2) - (ws_height / 2))) * ((float)TILE_SIZE / ws_height);
        color = tex->data[wich_tex][(TILE_SIZE * offy) + offx];
        my_mlx_pixel_put(&mlx, i, start++, color);
    }
    start = 0;
    while (start < ray.wall_top)
        my_mlx_pixel_put(&mlx, i, start++, tex->ciel);
    start = ray.wall_bottom;
    while (start < g_window.height)
        my_mlx_pixel_put(&mlx, i, start++, tex->floor);
}

void render_3d_projection(t_ray ray, t_texture *tex, int i)
{
    int wall_stripe_hieght;
    float correct_distance;
    float distance_proj_plane;

    correct_distance =
        ray.distance * cos(ray.ray_angle - g_player.rotation_angle);
    distance_proj_plane = (g_window.width / 2) / tan(FOV_ANGLE / 2);
    wall_stripe_hieght = (int)((TILE_SIZE / correct_distance) * distance_proj_plane);
    ray.wall_top = (g_window.height / 2) - (wall_stripe_hieght / 2);
    if (ray.wall_top < 0)
        ray.wall_top = 0;
    ray.wall_bottom = (g_window.height / 2) + (wall_stripe_hieght / 2);
    if (ray.wall_bottom > g_window.height)
        ray.wall_bottom = g_window.height;
    render_walls(ray, i, wall_stripe_hieght, tex);
}