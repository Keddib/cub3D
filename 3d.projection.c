/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.projection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 13:53:14 by keddib            #+#    #+#             */
/*   Updated: 2020/10/20 17:50:47 by keddib           ###   ########.fr       */
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

    while (start < ray.wall_bottom)
    {
        offy = (start - ((window.height / 2) - (ws_height / 2))) * ((float)TILE_SIZE / ws_height);
        // printf("%d\n", *tex->data[0]);
        // printf("x = %d\n", (TILE_SIZE * offy) + offx);
        color = tex->data[2][(TILE_SIZE * offy) + offx];
        // color = ray.was_hit_vertical ? 0xd3d3d3 : 0xffffff;
        my_mlx_pixel_put(&mlx, i, start++, color);
    }
    start = 0;
    while (start < ray.wall_top)
        my_mlx_pixel_put(&mlx, i, start++, 0x5cabf4);
    start = ray.wall_bottom;
    while (start < window.height)
        my_mlx_pixel_put(&mlx, i, start++, 0xc58b00);
}

void render_3d_projection(t_ray ray, t_texture *tex, int i)
{
    int wall_stripe_hieght;
    float correct_distance;
    float distance_proj_plane;

    correct_distance =
        ray.distance * cos(ray.ray_angle - player.rotation_angle);
    distance_proj_plane = (window.width / 2) / tan(FOV_ANGLE / 2);
    wall_stripe_hieght = (int)((TILE_SIZE / correct_distance) * distance_proj_plane);
    ray.wall_top = (window.height / 2) - (wall_stripe_hieght / 2);
    if (ray.wall_top < 0)
        ray.wall_top = 0;
    ray.wall_bottom = (window.height / 2) + (wall_stripe_hieght / 2);
    if (ray.wall_bottom > window.height)
        ray.wall_bottom = window.height;
    render_walls(ray, i, wall_stripe_hieght, tex);
}