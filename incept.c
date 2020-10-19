/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incept->c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keddib <keddib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 23:11:43 by keddib            #+#    #+#             */
/*   Updated: 2020/10/17 01:04:46 by keddib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void calc_distances(t_ray *ray, t_incept *incept)
{
    incept->horz_distance = incept->is_horz_hit
                                ? distance_between_points(player.x, player.y,
                                                          incept->horz_x, incept->horz_y)
                                : (float)INT_MAX;
    incept->vert_distance = incept->is_vert_hit
                                ? distance_between_points(player.x, player.y,
                                                          incept->vert_x, incept->vert_y)
                                : (float)INT_MAX;
}

void h_until_wall(float n_x, float n_y, t_incept *incept, t_ray *ray)
{
    while (n_x >= 0 && n_x <= window.width && n_y >= 0 && n_y <= window.height)
    {
        incept->check_x = n_x;
        incept->check_y = n_y + (ray->ray_facingup ? -1 : 0);

        if (is_this_wall(incept->check_x, incept->check_y))
        {
            incept->horz_x = n_x;
            incept->horz_y = n_y;
            incept->is_horz_hit = 1;
            break;
        }
        else
        {
            n_x += incept->xstep;
            n_y += incept->ystep;
        }
    }
}

void v_until_wall(float x, float y, t_incept *incept, t_ray *ray)
{
    while (x >= 0 && x <= window.width && y >= 0 && y <= window.height)
    {
        incept->check_x = x + (ray->ray_facingleft ? -1 : 0);
        incept->check_y = y;
        if (is_this_wall(incept->check_x, incept->check_y))
        {
            incept->vert_x = x;
            incept->vert_y = y;
            incept->is_vert_hit = 1;
            break;
        }
        else
        {
            x += incept->xstep;
            y += incept->ystep;
        }
    }
}
// Find the y-coordinate of the closest horizontal grid intersection
// Find the x-coordinate of the closest horizontal grid intersection
// Calculate the increment incept->xstep and incept->ystep
// Increment incept->xstep and incept->ystep until we find a wall

void get_horizontal(t_ray *ray, t_incept *incept)
{
    float next_x;
    float next_y;

    incept->is_horz_hit = 0;
    incept->horz_x = 0;
    incept->horz_y = 0;

    incept->yintercept = floor(player.y / TILE_SIZE) *
                         TILE_SIZE;
    incept->yintercept += ray->ray_facingdown ? TILE_SIZE : 0;

    incept->xintercept = player.x +
                         (incept->yintercept - player.y) / tan(ray->ray_angle);
    incept->ystep = TILE_SIZE;
    incept->ystep *= ray->ray_facingup ? -1 : 1;
    incept->xstep = TILE_SIZE / tan(ray->ray_angle);
    incept->xstep *= (ray->ray_facingleft && incept->xstep > 0) ? -1 : 1;
    incept->xstep *= (ray->ray_facingright && incept->xstep < 0) ? -1 : 1;
    next_x = incept->xintercept;
    next_y = incept->yintercept;

    h_until_wall(next_x, next_y, incept, ray);
}
// Find the x-coordinate of the closest vertical grid intersection
// Find the y-coordinate of the closest vertical grid intersection
// Calculate the increment incept->xstep and incept->ystep
// Increment incept->xstep and incept->ystep until we find a wall

void get_vertical(t_ray *ray, t_incept *incept)
{
    float next_x;
    float next_y;

    incept->is_vert_hit = 0;
    incept->vert_x = 0;
    incept->vert_y = 0;

    incept->xintercept = floor(player.x / TILE_SIZE) *
                         TILE_SIZE;
    incept->xintercept += ray->ray_facingright ? TILE_SIZE : 0;

    incept->yintercept = player.y +
                         (incept->xintercept - player.x) * tan(ray->ray_angle);

    incept->xstep = TILE_SIZE;
    incept->xstep *= ray->ray_facingleft ? -1 : 1;
    incept->ystep = TILE_SIZE * tan(ray->ray_angle);
    incept->ystep *= (ray->ray_facingup && incept->ystep > 0) ? -1 : 1;
    incept->ystep *= (ray->ray_facingdown && incept->ystep < 0) ? -1 : 1;
    next_x = incept->xintercept;
    next_y = incept->yintercept;

    v_until_wall(next_x, next_y, incept, ray);
}